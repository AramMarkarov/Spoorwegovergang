unsigned long lastBuzzerTime = 0;
bool buzzerState = false;

const unsigned long BUZZER_BLINK_INTERVAL = 250;
const unsigned long BUZZER_TICK_INTERVAL = 750;

bool threeTickActive = false;
int tickCount = 0;
int ticks = 3;

void buzzerOn(unsigned long now) {
  if (now - lastBuzzerTime >= BUZZER_BLINK_INTERVAL) {
    buzzerState = !buzzerState;
    digitalWrite(BUZZER, buzzerState ? HIGH : LOW);
    lastBuzzerTime = now;
  }
}

void buzzerOff() {
  digitalWrite(BUZZER, LOW);
}

void startThreeTickBuzzer(unsigned long now) {
  threeTickActive = true;
  tickCount = 0;
  buzzerState = false;
  lastBuzzerTime = now;
}


void updateThreeTickBuzzer(unsigned long now) {
  if (now - lastBuzzerTime >= BUZZER_TICK_INTERVAL) {
    buzzerState = !buzzerState;
    digitalWrite(BUZZER, buzzerState ? HIGH : LOW);
    lastBuzzerTime = now;
    tickCount++;

    if (tickCount >= ticks) {
      threeTickActive = false;
      digitalWrite(BUZZER, LOW);
    }
  }
}
