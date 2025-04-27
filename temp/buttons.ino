const int SENSOR_EAST = 4;
const int BUTTON_SOUTH = 5;
const int BUTTON_NORTH = 6;
const int SENSOR_WEST = 7;

const unsigned long debounceDelay = 50; // ms

unsigned long lastDebounceTimeNorth = 0;
unsigned long lastDebounceTimeSouth = 0;

int lastStableStateNorth = HIGH;
int lastReadingNorth = HIGH;

int lastStableStateSouth = HIGH;
int lastReadingSouth = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(SENSOR_EAST, INPUT_PULLUP);
  pinMode(SENSOR_WEST, INPUT_PULLUP);
  pinMode(BUTTON_SOUTH, INPUT_PULLUP);
  pinMode(BUTTON_NORTH, INPUT_PULLUP);
}

void loop() {
  // ----- Sensor East -----
  static int lastSensorEast = HIGH;
  int currentSensorEast = digitalRead(SENSOR_EAST);
  if (currentSensorEast == LOW && lastSensorEast == HIGH) {
    Serial.println("Sensor East triggered");
  }
  lastSensorEast = currentSensorEast;

  // ----- Sensor West -----
  static int lastSensorWest = HIGH;
  int currentSensorWest = digitalRead(SENSOR_WEST);
  if (currentSensorWest == LOW && lastSensorWest == HIGH) {
    Serial.println("Sensor West triggered");
  }
  lastSensorWest = currentSensorWest;

  // ----- Button North with debounce -----
  int readingNorth = digitalRead(BUTTON_NORTH);
  if (readingNorth != lastReadingNorth) {
    lastDebounceTimeNorth = millis();
  }

  if ((millis() - lastDebounceTimeNorth) > debounceDelay) {
    if (readingNorth != lastStableStateNorth) {
      lastStableStateNorth = readingNorth;
      if (readingNorth == LOW) {
        Serial.println("Button North pressed");
      }
    }
  }
  lastReadingNorth = readingNorth;

  // ----- Button South with debounce -----
  int readingSouth = digitalRead(BUTTON_SOUTH);
  if (readingSouth != lastReadingSouth) {
    lastDebounceTimeSouth = millis();
  }

  if ((millis() - lastDebounceTimeSouth) > debounceDelay) {
    if (readingSouth != lastStableStateSouth) {
      lastStableStateSouth = readingSouth;
      if (readingSouth == LOW) {
        Serial.println("Button South pressed");
      }
    }
  }
  lastReadingSouth = readingSouth;
}

