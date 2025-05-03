bool trainDetectedWest = false;
bool trainDetectedEast = false;

int lastSensorStateEast = LOW;
int lastSensorStateWest = LOW;
unsigned long lastSensorChangeTime = 0;

void handleTrainDetection() {
  int readingEast = digitalRead(SENSOREAST);
  int readingWest = digitalRead(SENSORWEST);

  if (readingEast != lastSensorStateEast || readingWest != lastSensorStateWest) {
    lastSensorChangeTime = millis();
  }

  if ((millis() - lastSensorChangeTime) > DEBOUNCE_DELAY) {
    if (readingWest == HIGH && !trainDetectedWest && !trainDetectedEast) {
      trainDetectedWest = true;
    }
    if (readingEast == HIGH && trainDetectedWest) {
      trainDetectedWest = false;
    }

    if (readingEast == HIGH && !trainDetectedWest && !trainDetectedEast) {
      trainDetectedEast = true;
      Serial.print("XD");
    }
    if (readingWest == HIGH && trainDetectedEast) {
      trainDetectedEast = false;
    }
  }

  lastSensorStateEast = readingEast;
  lastSensorStateWest = readingWest;
}
