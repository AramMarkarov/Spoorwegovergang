void setupTraffic() {
  currentTrafficState = SYSTEM_STARTUP;
}

void updateTraffic() {
  unsigned long now = millis();
  stateStartTime = 0;
  bool trainIncoming = trainDetectedEast || trainDetectedWest;
  bool trainPassed = !trainDetectedEast && !trainDetectedWest;

  switch (currentTrafficState) {

    case NORTH_GREEN:
      if (trainIncoming) {
        transitionToTrainApproaching();
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
        transitionToTrainApproaching();
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

    case TRAIN_APPROACHING:
      switch (lastTrafficState) {
        case NORTH_GREEN:
        case STARTUP_NORTH_GREEN:
          northToYellow();
          lastTrafficState = NORTH_YELLOW;
          stateStartTime = now;
          break;

        case SOUTH_GREEN:
        case STARTUP_SOUTH_GREEN:
          southToYellow();
          lastTrafficState = SOUTH_YELLOW;
          stateStartTime = now;
          break;

        case NORTH_YELLOW:
          if (now - stateStartTime >= YELLOW_TIME) {
            northToRed();
            lastTrafficState = NORTH_RED;
            stateStartTime = now;
          }
          break;

        case SOUTH_YELLOW:
          if (now - stateStartTime >= YELLOW_TIME) {
            southToRed();
            lastTrafficState = SOUTH_RED;
            stateStartTime = now;
          }
          break;

        case NORTH_RED:
        case SOUTH_RED:
        case SYSTEM_STARTUP:
          if (now - stateStartTime >= RED_TIME) {
            handleBlinkingYellow(now);
            closeBarrier(now);
          }
          break;

        default:
          break;
      }

      if (trainPassed) {
        transitionToTrainPassed();
        return;
      }
      break;

    case TRAIN_PASSED:
      openBarrier(now);
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


    case SYSTEM_STARTUP:
      northRed();
      southRed();
      openBarrier(now);
      displayDigit(7); // Display uit
      if (trainIncoming) {
        transitionToTrainApproaching();
        return;
      }

      if (buttonNorthPressed && !barrierIsMoving) {
        currentTrafficState = STARTUP_NORTH_GREEN;
        buttonSouthPressed = false;
        stateStartTime = now;
      } else if (buttonSouthPressed && !barrierIsMoving) {
        currentTrafficState = STARTUP_SOUTH_GREEN;
        buttonNorthPressed = false;
        stateStartTime = now;
      }
      break;

    case STARTUP_NORTH_GREEN:
      northGreen();

      if (trainIncoming) {
        stateStartTime = now;
        transitionToTrainApproaching();
        return;
      }

      if (now - stateStartTime >= MIN_GREEN_TIME) {
        currentTrafficState = NORTH_GREEN;
        stateStartTime = now;
      }

      break;

    case STARTUP_SOUTH_GREEN:
      southGreen();

      if (trainIncoming) {
        transitionToTrainApproaching();
        return;
      }

      if (now - stateStartTime >= MIN_GREEN_TIME) {
        currentTrafficState = SOUTH_GREEN;
        stateStartTime = now;
      }
      break;

    default:
      break;
  }
}
