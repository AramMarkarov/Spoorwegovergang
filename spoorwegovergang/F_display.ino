unsigned long lastDisplayUpdate = 0;
const unsigned long SECOND = 1000;

// Getallen 0-5 voor 7-segment display
const byte DIGITS[7] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B00000000, // off
};

unsigned long countdownStartTime = 0;
const long COUNTDOWN_SECONDS = 6; // 0 telt mee

// Juiste getal weergeven
void displayDigit(int number) {
  digitalWrite(LATCHPIN, LOW);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, DIGITS[number]);
  digitalWrite(LATCHPIN, HIGH);
}

const unsigned long DISPLAY_UPDATE_INTERVAL = 100;

void updateDisplayCounter(unsigned long now) {
  if (now - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL) {
    lastDisplayUpdate = now;

    unsigned long elapsed = now - countdownStartTime;
    int secondsLeft = COUNTDOWN_SECONDS - (elapsed / SECOND);

    if (secondsLeft >= 0 && secondsLeft < COUNTDOWN_SECONDS) {
      displayDigit(secondsLeft);
    }
  }
}

