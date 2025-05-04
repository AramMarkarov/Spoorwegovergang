int displayCounter = -1;
unsigned long lastDisplayUpdate = 0;
const unsigned long SECOND = 1000;

// Getallen 0-5 voor 7-segment display
const byte digits[7] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B00000000, // off
};

unsigned long countdownStartTime = 0;
const int countdownSeconds = 5;
bool countdownActive = false;

// Juiste getal weergeven
void displayDigit(int number) {
  digitalWrite(LATCHPIN, LOW);
  shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, digits[number]);
  digitalWrite(LATCHPIN, HIGH);
}

// Aftellen
void startCountdown() {
  countdownActive = true;
}

bool isCountdownFinished(unsigned long now) {
  countdownStartTime = now;
  return countdownActive && ((now - countdownStartTime) >= countdownSeconds * SECOND);
}

const unsigned long DISPLAY_UPDATE_INTERVAL = 250;
// Zorgt dat display daadwerkelijk aftelt naar 0, dan countdownActive op false
void updateDisplayCounter(unsigned long now) {
  if (!countdownActive) return;

  if (now - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL) {
    lastDisplayUpdate = now;

    unsigned long elapsed = now - countdownStartTime;
    int secondsLeft = countdownSeconds - (elapsed / SECOND);

    if (secondsLeft >= 0 && secondsLeft < (sizeof(digits) / sizeof(digits[0]))) {
      displayDigit(secondsLeft);
    }

    if (secondsLeft <= 0) {
      countdownActive = false;
    }
  }
}
