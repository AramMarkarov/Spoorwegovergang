int displayCounter = -1;
unsigned long lastDisplayUpdate = 0;
const unsigned long MILLIS_IN_SECOND = 1000;

// Getallen 0-5 voor 7-segment display
const byte digits[6] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
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
  countdownStartTime = millis();
  countdownActive = true;
}

bool isCountdownFinished() {
  return countdownActive && ((millis() - countdownStartTime) 
  >= countdownSeconds * MILLIS_IN_SECOND);
}

// Zorgt dat display daadwerkelijk aftelt naar 0, dan countdownActive op false
void updateDisplayCounter() {
  if (!countdownActive) return;

  unsigned long elapsed = millis() - countdownStartTime;
  int secondsLeft = countdownSeconds - (elapsed / MILLIS_IN_SECOND);

  
if (secondsLeft >= 0 && secondsLeft < (sizeof(digits) / sizeof(digits[0]))) {
    displayDigit(secondsLeft);
  }

  if (secondsLeft <= 0) {
    countdownActive = false;
  }
}
