unsigned long lastBuzzerTime = 0; // Tijd sinds de laatste buzzer 

void buzzerOn(unsigned long now) {
  const unsigned long TICK = 250;
  const unsigned long BEEP_DURATION = 100;
  const int BUZZER_FREQ = 800;

  if (now - lastBuzzerTime >= TICK) {
    tone(BUZZER, BUZZER_FREQ, BEEP_DURATION);
    lastBuzzerTime = now;
  }
}

void buzzerOff() {
  noTone(BUZZER);
}

int tickStep = 0;

void threeTicks(unsigned long now) {
  const unsigned long TICK = 750;
  const unsigned long NUMBER_OF_TICKS = 3;
  const unsigned long SEQUENCE_LENGTH = 4;
  const int BUZZER_FREQ = 800;
  const unsigned long BEEP_DURATION = 500;

  if (tickStep < NUMBER_OF_TICKS) {
    if (now - lastBuzzerTime >= TICK) {
      tone(BUZZER, BUZZER_FREQ, BEEP_DURATION);
      lastBuzzerTime = now;
      tickStep++;
    }
  } else if (tickStep < SEQUENCE_LENGTH) {
    if (now - lastBuzzerTime >= TICK) {
      lastBuzzerTime = now;
      tickStep++;
    }
  } else {
    tickStep = 0;  // Reset voor volgende cyclus
  }
}

