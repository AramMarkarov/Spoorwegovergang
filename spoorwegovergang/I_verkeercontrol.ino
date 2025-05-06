// Timers voor de verkeerslichten, wachttijden tussen de verschillende fases
const unsigned long MIN_GREEN_TIME = 12000;
const unsigned long YELLOW_TIME = 2000;
const unsigned long RED_TIME = 3000;
const unsigned long BLINK_INTERVAL = 500;

// Timer die iedere bij iedere fase gebruikt voor timers
unsigned long stateStartTime = millis();

// Wederom state machine voor de fases
enum TrafficState {
  NORTH_GREEN,
  NORTH_YELLOW,
  NORTH_RED,
  SOUTH_GREEN,
  SOUTH_YELLOW,
  SOUTH_RED,
  TRAIN_APPROACHING,
  TRAIN_PASSING,
  TRAIN_PASSED,
  COUNTDOWN,
  SYSTEM_STARTUP,
  SYSTEM_STANDBY,
};

TrafficState currentTrafficState; // Huidige fase van de verkeerslichten
TrafficState lastTrafficState; // Vorige fase van de verkeerslichten, nodig
                               // voor overgaan naar TRAIN_APPROACHING
unsigned long lastBlinkTime = 0; // Timer voor knipperen van de lichten
bool yellowBlinkState = false;

// Knoppen voor de verkeerslichten
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

// Geel knipperen van de verkeerslichten
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
// Fase naar TRAIN_APPROACHING, methode omdat het vaak voorkomt
void transitionToTrainApproaching() {
  lastTrafficState = currentTrafficState;
  currentTrafficState = TRAIN_APPROACHING;
}
