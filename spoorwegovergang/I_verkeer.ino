void setupTraffic() {
  northGreen();
  southRed();
  currentTrafficState = NORTH_GREEN;
  stateStartTime = millis();
}

void updateTraffic() {
  unsigned long now = millis();
  bool trainIncoming = trainDetectedEast || trainDetectedWest; // heeft rework nodig

  switch (currentTrafficState) {

    case NORTH_GREEN:
      if (trainIncoming) {
        transitionToTrainApproaching(now);
        return;
      }

      if (buttonSouthPressed && (now - stateStartTime >= MIN_GREEN_TIME)) {
        northToYellow();
        currentTrafficState = NORTH_YELLOW;
        stateStartTime = now;
      }
      break;

    case NORTH_YELLOW:
      if (now - stateStartTime >= YELLOW_TIME) {
        northToRed();
        currentTrafficState = NORTH_RED;
        stateStartTime = now;
      }
      break;

    case NORTH_RED:
      if (now - stateStartTime >= RED_TIME) {
        southGreen();
        currentTrafficState = SOUTH_GREEN;
        stateStartTime = now;
      }
      break;

    case SOUTH_GREEN:
      if (trainIncoming) {
        transitionToTrainApproaching(now);
        return;
      }

      if (buttonNorthPressed && (now - stateStartTime >= MIN_GREEN_TIME)) {
        southToYellow();
        currentTrafficState = SOUTH_YELLOW;
        stateStartTime = now;
      }
      break;

    case SOUTH_YELLOW:
      if (now - stateStartTime >= YELLOW_TIME) {
        southToRed();
        currentTrafficState = SOUTH_RED;
        stateStartTime = now;
      }
      break;

    case SOUTH_RED:
      if (now - stateStartTime >= RED_TIME) {
        northGreen();
        currentTrafficState = NORTH_GREEN;
        stateStartTime = now;
      }
      break;

    case TRAIN_APPROACHING: // heeft een rework nodig
      handleServoForClosing();

      if (isCountdownFinished()) {
        currentTrafficState = TRAIN_PASSED;
        stateStartTime = now;
      }

      break;

    case TRAIN_PASSED: // heeft een rework nodig
      openBarrier();
      buzzerOff();
      if (buttonNorthPressed) {
        currentTrafficState = NORTH_GREEN;
        buttonSouthPressed = false;
      } else if (buttonSouthPressed) {
        currentTrafficState = SOUTH_GREEN;
        buttonNorthPressed = false;
      } else {
        currentTrafficState = NORTH_GREEN;
      }
      // stel in voor system startup en correct button functie
      stateStartTime = now;
      break;

    default:
      break;
  }
}
