void setupTraffic() { // Startpunt programma
  currentTrafficState = SYSTEM_STARTUP;
  barrierCount = true;
}

void updateTraffic() { // Hoofdloop van het programma
  unsigned long now = millis(); // Huidige tijd (simuleert currentMillis en
                                // previousMillis)
  bool trainWasDetected = detectionPhase != NO_TRAIN; // Check voor trein

  switch (currentTrafficState) {

    case NORTH_GREEN:
      northGreen();
      if (trainWasDetected) { // Trein detectie, komt vaker voor
        transitionToTrainApproaching();
        return;
      }

      // Check of de knop is ingedrukt, komt vaker voor met 12 seconden wachten
      // als eerder groen is ingedrukt
      if (buttonSouthPressed && (now - stateStartTime >= MIN_GREEN_TIME)) {
        northToYellow();
        currentTrafficState = NORTH_YELLOW;
        stateStartTime = now;
      }
      break;

    case NORTH_YELLOW:
      if (now - stateStartTime >= YELLOW_TIME) { // 2 seconden wachten
        northToRed();
        currentTrafficState = NORTH_RED;
        stateStartTime = now;
      }
      break;

    case NORTH_RED:
      if (now - stateStartTime >= RED_TIME) { // 3 seconden wachten
        southGreen();
        currentTrafficState = SOUTH_GREEN;
        stateStartTime = now;
      }
      break;

    case SOUTH_GREEN:
      southGreen();
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

    case TRAIN_APPROACHING: // lastTrafficState regelt de volgorde van de
                           // verkeerslichten om de spoorwegovergang te sluiten
      switch (lastTrafficState) {
        case NORTH_GREEN:
          northToYellow();
          lastTrafficState = NORTH_YELLOW;
          stateStartTime = now;
          break;

        case SOUTH_GREEN:
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
        // De verkeerslichten zijn nu rood, de spoorwegovergang kan sluiten
        case NORTH_RED:
        case SOUTH_RED:
          if (now - stateStartTime >= RED_TIME) {
            handleBlinkingYellow(now);
            closeBarrier();

            if (barrierIsMoving) {
              buzzerOn(now);
              // 16 seconden wachten voor de spoorbomen
              if (now - stateStartTime >= BARRIER_MOVE_TIME_MS) {
                barrierIsMoving = false;
                currentTrafficState = TRAIN_PASSING;
                stateStartTime = now;
              }
            }
          }
          break;
        // De verkeerslichten zijn nu rood, de spoorwegovergang kan sluiten
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
    // Trein is momenteel aan het passeren, de spoorwegovergang blijft dicht
    // totdat de trein bij tweede sensor is gepasseerd
    case TRAIN_PASSING:
      handleBlinkingYellow(now);

      if (trainPassed) {
        stateStartTime = now;
        barrierCount = true;
        currentTrafficState = TRAIN_PASSED;
        return;
      }

      break;
    // Trein is gepasseerd, de spoorwegovergang kan weer open
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
    // Aftellen en het tickpatroon
    case COUNTDOWN:
      handleBlinkingYellow(now);
      updateDisplayCounter(now);
      threeTicks(now);

      if ((now - countdownStartTime) >= COUNTDOWN_SECONDS * SECOND) {
        displayDigit(0);
        currentTrafficState = SYSTEM_STANDBY;
        stateStartTime = now;
      }
      break;
    // Opstartcase, geel knippert en rood brandt aan beide kanten. Ook gaan de
    // spoorbomen open (standaard is het dicht)
    case SYSTEM_STARTUP:
      openBarrier();
      displayDigit(7);
      handleBlinkingYellow(now);

      if (trainWasDetected) {
        transitionToTrainApproaching();
        stateStartTime = now;
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
    // Standby na trein passage of opstarten
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
        currentTrafficState = NORTH_GREEN;
        buttonSouthPressed = false;
        displayDigit(7);
        stateStartTime = now;
      } else if (buttonSouthPressed && !barrierIsMoving) {
        currentTrafficState = SOUTH_GREEN;
        buttonNorthPressed = false;
        displayDigit(7);
        stateStartTime = now;
      }

      break;

    default:
      break;
  }
}
