const unsigned long MIN_GREEN_TIME = 12000;
const unsigned long YELLOW_TIME = 2000;
const unsigned long RED_TIME = 3000;
const unsigned long BLINK_INTERVAL = 500;

enum TrafficState {
  NORTH_GREEN,
  NORTH_YELLOW,
  NORTH_RED,
  SOUTH_GREEN,
  SOUTH_YELLOW,
  SOUTH_RED,
  TRAIN_APPROACHING,
  TRAIN_PASSED
};

TrafficState currentTrafficState = NORTH_GREEN;
unsigned long lastBlinkTime = 0;
bool yellowBlinkState = false;

void northGreen() {
  digitalWrite(RED_NORTH, LOW);
  digitalWrite(YELLOW_NORTH, LOW);
  digitalWrite(GREEN_NORTH, HIGH);
}

void northToYellow() {
  digitalWrite(GREEN_NORTH, LOW);
  digitalWrite(YELLOW_NORTH, HIGH);
}

void northToRed() {
  digitalWrite(YELLOW_NORTH, LOW);
  digitalWrite(RED_NORTH, HIGH);
  buttonNorthPressed = false;
}

void northRed() {
  digitalWrite(GREEN_NORTH, LOW);
  digitalWrite(YELLOW_NORTH, LOW);
  digitalWrite(RED_NORTH, HIGH);
}

void southGreen() {
  digitalWrite(RED_SOUTH, LOW);
  digitalWrite(YELLOW_SOUTH, LOW);
  digitalWrite(GREEN_SOUTH, HIGH);
}

void southToYellow() {
  digitalWrite(GREEN_SOUTH, LOW);
  digitalWrite(YELLOW_SOUTH, HIGH);
}

void southToRed() {
  digitalWrite(YELLOW_SOUTH, LOW);
  digitalWrite(RED_SOUTH, HIGH);
  buttonSouthPressed = false;
}

void southRed() {
  digitalWrite(GREEN_SOUTH, LOW);
  digitalWrite(YELLOW_SOUTH, LOW);
  digitalWrite(RED_SOUTH, HIGH);
}

void handleBlinkingYellow(unsigned long now) {
  digitalWrite(RED_NORTH, HIGH);
  digitalWrite(RED_SOUTH, HIGH);

  if (now - lastBlinkTime >= BLINK_INTERVAL) {
    yellowBlinkState = !yellowBlinkState;
    digitalWrite(YELLOW_NORTH, yellowBlinkState ? HIGH : LOW);
    digitalWrite(YELLOW_SOUTH, yellowBlinkState ? HIGH : LOW);
    lastBlinkTime = now;
  }
}

void transitionToTrainApproaching(unsigned long now) {
  currentTrafficState = TRAIN_APPROACHING;
  startCountdown();
  buzzerOn();
  closeBarrier();
  stateStartTime = now;
}

void handleServoForClosing() {
  if (currentTrafficState == TRAIN_PASSED) {
    closeBarrier();
  }
}

void countdownDisplay() {
  if (!countdownActive) {
    startCountdown();
  }
}

void buzzerOn() {
  digitalWrite(BUZZER, HIGH);
}

void buzzerOff() {
  digitalWrite(BUZZER, LOW);
}
