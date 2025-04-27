const unsigned long MIN_GREEN_TIME = 12000;
const unsigned long YELLOW_TIME = 2000;
const unsigned long ALL_RED_TIME = 3000;

// Enum is vergelijkbaar met een enkele array
enum TrafficState {
  NORTH_GREEN,
  NORTH_YELLOW,
  ALL_RED_FROM_NORTH,
  SOUTH_GREEN,
  SOUTH_YELLOW,
  ALL_RED_FROM_SOUTH
};

TrafficState currentTrafficState = NORTH_GREEN;
unsigned long stateStartTime = 0;

// Startpunt bij opstarten van de Arduino
void setupTrafficLights() {
  northGreen();
  southRed();
  currentTrafficState = NORTH_GREEN;
  stateStartTime = millis();
}

// Loop functie die continu draait om de verkeerslichten te controleren
void updateTrafficLights() {
  unsigned long now = millis();

  switch (currentTrafficState) {
    case NORTH_GREEN:
      if (buttonNorthPressed && (now - stateStartTime >= MIN_GREEN_TIME)) {
        northToYellow();
        currentTrafficState = NORTH_YELLOW;
        stateStartTime = now;
      }
      break;

    case NORTH_YELLOW:
      if (now - stateStartTime >= YELLOW_TIME) {
        northToRed();
        currentTrafficState = ALL_RED_FROM_NORTH;
        stateStartTime = now;
      }
      break;

    case ALL_RED_FROM_NORTH:
      if (now - stateStartTime >= ALL_RED_TIME) {
        southGreen();
        currentTrafficState = SOUTH_GREEN;
        stateStartTime = now;
      }
      break;

    case SOUTH_GREEN:
      if (buttonSouthPressed && (now - stateStartTime >= MIN_GREEN_TIME)) {
        southToYellow();
        currentTrafficState = SOUTH_YELLOW;
        stateStartTime = now;
      }
      break;

    case SOUTH_YELLOW:
      if (now - stateStartTime >= YELLOW_TIME) {
        southToRed();
        currentTrafficState = ALL_RED_FROM_SOUTH;
        stateStartTime = now;
      }
      break;

    case ALL_RED_FROM_SOUTH:
      if (now - stateStartTime >= ALL_RED_TIME) {
        northGreen();
        currentTrafficState = NORTH_GREEN;
        stateStartTime = now;
      }
      break;
  }
}

// --- Traffic Light Control Functies ---

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
}

void southRed() {
  digitalWrite(GREEN_SOUTH, LOW);
  digitalWrite(YELLOW_SOUTH, LOW);
  digitalWrite(RED_SOUTH, HIGH);
}
