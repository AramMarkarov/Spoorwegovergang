const unsigned long MIN_GREEN_TIME = 12000;
const unsigned long YELLOW_TIME = 2000;
const unsigned long RED_TIME = 3000;
const unsigned long BLINK_INTERVAL = 500;
unsigned long stateStartTime = millis();

enum TrafficState {
  NORTH_GREEN,
  NORTH_YELLOW,
  NORTH_RED,
  SOUTH_GREEN,
  SOUTH_YELLOW,
  SOUTH_RED,
  TRAIN_APPROACHING,
  TRAIN_PASSED,
  SYSTEM_STARTUP,
  SYSTEM_STANDBY,
  STARTUP_NORTH_GREEN,
  STARTUP_SOUTH_GREEN
};

TrafficState currentTrafficState;
TrafficState lastTrafficState;
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

void transitionToTrainApproaching() {
  lastTrafficState = currentTrafficState; // Check verkeerstatus
  currentTrafficState = TRAIN_APPROACHING;
}

void transitionToTrainPassed() {
  currentTrafficState = TRAIN_PASSED;
}

void countdownDisplay() {
  if (!countdownActive) {
    startCountdown();
  }
}
