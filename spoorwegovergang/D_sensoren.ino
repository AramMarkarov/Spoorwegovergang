enum TrainDetectionPhase {
  NO_TRAIN,
  TRAIN_EAST_DETECTED,
  TRAIN_WEST_DETECTED,
  TRAIN_PASSED_DETECTION,
};

TrainDetectionPhase detectionPhase = NO_TRAIN;

bool trainPassed = false;
unsigned long lastSensorChangeTime = 0;
bool lastSensorStateEast = false;
bool lastSensorStateWest = false;

void handleTrainDetection() {
  currentMillis = millis();
  int readingEast = digitalRead(SENSOREAST);
  int readingWest = digitalRead(SENSORWEST);

  if (readingEast != lastSensorStateEast || readingWest != lastSensorStateWest) {
    lastSensorChangeTime = currentMillis;
  }

  if ((currentMillis - lastSensorChangeTime) > DEBOUNCE_DELAY) {
    switch (detectionPhase) {
      case NO_TRAIN:
        if (readingEast == HIGH) {
          detectionPhase = TRAIN_EAST_DETECTED;
        } else if (readingWest == HIGH) {
          detectionPhase = TRAIN_WEST_DETECTED;
        }
        break;

      case TRAIN_EAST_DETECTED:
        if (readingWest == HIGH) {
          detectionPhase = TRAIN_PASSED_DETECTION;
          trainPassed = true;
        }
        break;

      case TRAIN_WEST_DETECTED:
        if (readingEast == HIGH) {
          detectionPhase = TRAIN_PASSED_DETECTION;
          trainPassed = true;
        }
        break;

      case TRAIN_PASSED_DETECTION:
        if (readingEast == LOW && readingWest == LOW) {
          detectionPhase = NO_TRAIN;
          trainPassed = false;
        }
        break;
    }
  }

  lastSensorStateEast = readingEast;
  lastSensorStateWest = readingWest;
}
