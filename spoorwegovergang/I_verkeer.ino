void setupTraffic() {
  northGreen();
  southRed();
  currentTrafficState = NORTH_GREEN;
  stateStartTime = millis();
}

void updateTraffic() {
  unsigned long now = millis();

  handleTrainDetection();

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

    case TRAIN_APPROACHING:
      handleBlinkingYellow(now);
      buzzerOn();
      break;

    case TRAIN_CROSSING:
      countdownDisplay();
      handleServoForClosing();
      buzzerOn();
      break;
  }
}
