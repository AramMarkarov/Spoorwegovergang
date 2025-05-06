enum TrainDetectionPhase { // State machine voor trein detectie
  NO_TRAIN,
  TRAIN_EAST_DETECTED,
  TRAIN_WEST_DETECTED,
  TRAIN_PASSED_DETECTION,
};

TrainDetectionPhase detectionPhase = NO_TRAIN; // Startfase, geen trein

bool trainPassed = false;
unsigned long lastSensorChangeTime = 0; // Track de laatste tijd dat de knop is ingedrukt
bool lastSensorStateEast = false; // Vorige status van sensoren
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
      case NO_TRAIN: // Geen trein gedetecteerd, wachten op een trein
        if (readingEast == HIGH) {
          detectionPhase = TRAIN_EAST_DETECTED;
        } else if (readingWest == HIGH) {
          detectionPhase = TRAIN_WEST_DETECTED;
        }
        break;

      case TRAIN_EAST_DETECTED: // Trein van oost naar west gedetecteerd
        if (readingWest == HIGH) {
          detectionPhase = TRAIN_PASSED_DETECTION;
          trainPassed = true;
        }
        break;

      case TRAIN_WEST_DETECTED: // Trein van west naar oost gedetecteerd
        if (readingEast == HIGH) {
          detectionPhase = TRAIN_PASSED_DETECTION;
          trainPassed = true;
        }
        break;

      case TRAIN_PASSED_DETECTION: // Trein is gepasseerd
        if (readingEast == LOW && readingWest == LOW) {
          detectionPhase = NO_TRAIN;
          trainPassed = false;
        }
        break;
    }
  }

  lastSensorStateEast = readingEast; // Update de vorige status van de sensor
  lastSensorStateWest = readingWest;
}
