const unsigned long DEBOUNCE_DELAY = 50; // Debounce
unsigned long lastButtonPressTime = 0; // Track de laatste tijd dat de knop is ingedrukt
int lastButtonStateNorth = LOW; // Vorige status van knoppen
int lastButtonStateSouth = LOW;

bool buttonNorthPressed = false; // Huidige status van knoppen
bool buttonSouthPressed = false;

unsigned long currentMillis; // Wordt gebruikt voor knoppen en sensoren

void handleButtonPress() { // Knopdrukken detectie
  currentMillis = millis(); // Huidige tijd in milliseconden
  int readingNorth = digitalRead(BUTTONNORTH);
  int readingSouth = digitalRead(BUTTONSOUTH);
  
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

  lastButtonStateNorth = readingNorth; // Update de vorige status van de knop
  lastButtonStateSouth = readingSouth;
}
