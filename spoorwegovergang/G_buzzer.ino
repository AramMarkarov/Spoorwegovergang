unsigned long lastBuzzerTime = 0;
bool buzzerState = false;

const unsigned long BUZZER_BLINK_INTERVAL = 250;
const unsigned long BUZZER_TICK_INTERVAL = 750;

// Barrier movement buzzer (blinking)
void buzzerOn(unsigned long now) {
  static unsigned long lastTick = 0;
  static bool buzzerTickState = false;

  if (now - lastTick >= BUZZER_BLINK_INTERVAL) {
    buzzerTickState = !buzzerTickState;
    digitalWrite(BUZZER, buzzerTickState ? HIGH : LOW);
    lastTick = now;
  }
}

void buzzerOff() {
  digitalWrite(BUZZER, LOW);
}

bool threeTickActive = false;
int tickCount = 0;
bool isBuzzing = false;
unsigned long lastTickTime = 0;

void startThreeTickBuzzer(unsigned long now) {
  threeTickActive = true;
  tickCount = 0;
  isBuzzing = false;
  lastTickTime = now;
}

void updateThreeTickBuzzer(unsigned long now) {
  if (!threeTickActive) return;

  if (now - lastTickTime >= BUZZER_TICK_INTERVAL) {
    isBuzzing = !isBuzzing;
    digitalWrite(BUZZER, isBuzzing ? HIGH : LOW);
    lastTickTime = now;

    if (!isBuzzing) {
      tickCount++;
      if (tickCount >= 3) {
        threeTickActive = false;
        digitalWrite(BUZZER, LOW);
      }
    }
  }
}
