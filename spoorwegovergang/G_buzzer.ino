unsigned long lastBuzzerTime = 0;
int tickCount = 0;
bool buzzerState = false;

const unsigned long BUZZER_BLINK_INTERVAL = 200;
const unsigned long BUZZER_TICK_INTERVAL = 300;
const unsigned long BUZZER_TICK_PAUSE = 800;

void startThreeTickBuzzer(unsigned long now) {
  static int tickCount = 0;
  static unsigned long lastTickTime = 0;
  static bool isBuzzing = false;
  static bool inPause = false;

  if (inPause) {
    if (now - lastTickTime >= BUZZER_TICK_PAUSE) {
      tickCount = 0;
      inPause = false;
      lastTickTime = now;
    }
    return;
  }

  if (now - lastTickTime >= BUZZER_TICK_INTERVAL) {
    isBuzzing = !isBuzzing;
    digitalWrite(BUZZER, isBuzzing ? HIGH : LOW);

    if (!isBuzzing) {
      tickCount++;
      if (tickCount >= 3) {
        inPause = true;
      }
    }
    lastTickTime = now;
  }
}

void buzzerOn(unsigned long now) {
  static unsigned long lastTick = 0;
  static bool buzzerTickState = false;

  if (barrierIsMoving) {
    if (now - lastTick >= BUZZER_BLINK_INTERVAL) {
      buzzerTickState = !buzzerTickState;
      digitalWrite(BUZZER, buzzerTickState ? HIGH : LOW);
      lastTick = now;
    }
  }
}

void buzzerOff() {
  digitalWrite(BUZZER, LOW);
}
