enum BuzzerMode {
  BUZZER_OFF,
  BUZZER_BLINKING,
  BUZZER_THREE_TICKS
};

BuzzerMode currentBuzzerMode = BUZZER_OFF;
unsigned long lastBuzzerTime = 0;
int tickCount = 0;
bool buzzerState = false;

const unsigned long BUZZER_BLINK_INTERVAL = 200;
const unsigned long BUZZER_TICK_INTERVAL = 300;
const unsigned long BUZZER_TICK_PAUSE = 800;
const unsigned long DISPLAY_UPDATE_INTERVAL = 1000;

// Buzzer statussen
void updateBuzzerDisplay() {
  unsigned long now = millis();

  switch (currentBuzzerMode) {
    case BUZZER_OFF:
      digitalWrite(BUZZER, LOW);
      break;

    case BUZZER_BLINKING:
      if (now - lastBuzzerTime >= BUZZER_BLINK_INTERVAL) {        
        buzzerState = !buzzerState;
        digitalWrite(BUZZER, buzzerState ? HIGH : LOW);
        lastBuzzerTime = now;
      }
      break;

    case BUZZER_THREE_TICKS:
      if (tickCount < 3) {
        if (now - lastBuzzerTime >= BUZZER_TICK_INTERVAL) {
          buzzerState = !buzzerState;
          digitalWrite(BUZZER, buzzerState ? HIGH : LOW);
          if (!buzzerState) tickCount++;
          lastBuzzerTime = now;
        }
      } else {
        if (now - lastBuzzerTime >= BUZZER_TICK_PAUSE) {
          tickCount = 0;
          lastBuzzerTime = now;
        }
      }
      break;
  }

  if (displayCounter >= 0) {
    if (now - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL) {
      displayCounter--;
      displayDigit(displayCounter);
      lastDisplayUpdate = now;

      if (displayCounter < 0) {
        currentBuzzerMode = BUZZER_OFF;
      }
    }
  }
}

void startBlinkingBuzzer() {
  currentBuzzerMode = BUZZER_BLINKING;
  lastBuzzerTime = millis();
  buzzerState = false;
}

void stopBuzzer() {
  currentBuzzerMode = BUZZER_OFF;
  digitalWrite(BUZZER, LOW);
}

void startThreeTickBuzzer() {
  currentBuzzerMode = BUZZER_THREE_TICKS;
  lastBuzzerTime = millis();
  tickCount = 0;
  buzzerState = false;
}
