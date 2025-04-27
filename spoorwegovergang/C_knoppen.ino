const unsigned long DEBOUNCE_DELAY = 50;
unsigned long lastButtonPressTime = 0;
int lastButtonStateNorth = LOW;
int lastButtonStateSouth = LOW;

bool buttonNorthPressed = false;
bool buttonSouthPressed = false;
unsigned long buttonPressTime = 0;

void handleButtonPress() {
  int readingNorth = digitalRead(BUTTONNORTH);
  int readingSouth = digitalRead(BUTTONSOUTH);
  
  // Setup voor debounce voor Noord en Zuid
  if (readingNorth != lastButtonStateNorth) {
    lastButtonPressTime = millis();
  }

  if (readingSouth != lastButtonStateSouth) {
    lastButtonPressTime = millis();
  }

  // Check of knopppen worden ingedrukt
  if ((millis() - lastButtonPressTime) > DEBOUNCE_DELAY) {
    if (readingNorth == HIGH && !buttonNorthPressed) {
      buttonNorthPressed = true;
      buttonPressTime = millis();
    }

    if (readingSouth == HIGH && !buttonSouthPressed) {
      buttonSouthPressed = true;
      buttonPressTime = millis();
    }
  }

  lastButtonStateNorth = readingNorth;
  lastButtonStateSouth = readingSouth;
}
