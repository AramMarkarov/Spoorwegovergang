const unsigned long DEBOUNCE_DELAY = 50;
unsigned long lastButtonPressTime = 0;
int lastButtonStateNorth = LOW;
int lastButtonStateSouth = LOW;

bool buttonNorthPressed = false;
bool buttonSouthPressed = false;

unsigned long currentMillis;

void handleButtonPress() {
  currentMillis = millis();
  int readingNorth = digitalRead(BUTTONNORTH);
  int readingSouth = digitalRead(BUTTONSOUTH);
  
  // Debounce
  if (readingNorth != lastButtonStateNorth || readingSouth != lastButtonStateSouth) {
    lastButtonPressTime = currentMillis;
  }

  if ((currentMillis - lastButtonPressTime) > DEBOUNCE_DELAY) {
    if (readingNorth == HIGH && !buttonNorthPressed) {
      buttonNorthPressed = true;
    }

    if (readingSouth == HIGH && !buttonSouthPressed) {
      buttonSouthPressed = true;
    }
  }

  lastButtonStateNorth = readingNorth;
  lastButtonStateSouth = readingSouth;
}
