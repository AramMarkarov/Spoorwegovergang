void setupTraffic() {
  currentTrafficState = SYSTEM_STARTUP;
}

void updateTraffic() {
  unsigned long now = millis();
  bool trainWasDetected = detectionPhase != NO_TRAIN;

  switch (currentTrafficState) {

    case NORTH_GREEN:
      if (trainWasDetected) {
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
      if (trainWasDetected) {
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
          if (now - stateStartTime >= RED_TIME) {
            handleBlinkingYellow(now);
            closeBarrier();

            if (barrierIsMoving) {
              buzzerOn(now);

              if (now - stateStartTime >= BARRIER_MOVE_TIME_MS) {
                barrierIsMoving = false;
                currentTrafficState = TRAIN_PASSING;
                stateStartTime = now;
              }
            }
          }
          break;
        case SYSTEM_STARTUP:
        case SYSTEM_STANDBY:
          handleBlinkingYellow(now);
          closeBarrier();

          if (barrierIsMoving) {
            buzzerOn(now);

            if (now - stateStartTime >= BARRIER_MOVE_TIME_MS) {
              barrierIsMoving = false;
              currentTrafficState = TRAIN_PASSING;
              stateStartTime = now;
            }
          }
          break;

        default:
          break;
      }

      break;

    case TRAIN_PASSING:
      handleBlinkingYellow(now);

      if (trainPassed) {
        stateStartTime = now;
        currentTrafficState = TRAIN_PASSED;
        return;
      }

      break;

    case TRAIN_PASSED:
      openBarrier();
      handleBlinkingYellow(now);

      if (barrierIsMoving) {
        buzzerOn(now);

        if (now - stateStartTime >= BARRIER_MOVE_TIME_MS) {
          barrierIsMoving = false;
          buzzerOff();

          countdownStartTime = now;
          lastDisplayUpdate = now;
          currentTrafficState = COUNTDOWN;
        }
      } else {
        buzzerOff();
      }
      break;

    case COUNTDOWN:
      handleBlinkingYellow(now);
      updateDisplayCounter(now);

      if ((now - countdownStartTime) >= COUNTDOWN_SECONDS * SECOND) {
        currentTrafficState = THREE_TICK;
        startThreeTickBuzzer(now);
        stateStartTime = now;
      }
      break;

    case THREE_TICK:
      updateThreeTickBuzzer(now);
      displayDigit(0);

      if (!threeTickActive) {
        currentTrafficState = SYSTEM_STANDBY;
        stateStartTime = now;  
      }
      break;

    case SYSTEM_STARTUP:
      northRed();
      southRed();
      openBarrier();
      displayDigit(7);

      if (trainWasDetected) {
        transitionToTrainApproaching();
        return;
      }

      if (barrierIsMoving) {
        buzzerOn(now);
        if (now - stateStartTime >= BARRIER_MOVE_TIME_MS) {
          barrierIsMoving = false;
          currentTrafficState = SYSTEM_STANDBY;
          stateStartTime = now;
        }
      } else {
        buzzerOff();
      }

      break;

    case SYSTEM_STANDBY:
      northRed();
      southRed();

      if (trainWasDetected) {
        stateStartTime = now;
        displayDigit(7);
        transitionToTrainApproaching();
        return;
      }

      buzzerOff();
      if (buttonNorthPressed && !barrierIsMoving) {
        currentTrafficState = STARTUP_NORTH_GREEN;
        buttonSouthPressed = false;
        displayDigit(7);
        stateStartTime = now;
      } else if (buttonSouthPressed && !barrierIsMoving) {
        currentTrafficState = STARTUP_SOUTH_GREEN;
        buttonNorthPressed = false;
        displayDigit(7);
        stateStartTime = now;
      }

      break;

    case STARTUP_NORTH_GREEN:
      northGreen();

      if (trainWasDetected) {
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

      if (trainWasDetected) {
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
