unsigned long lastBuzzerTime = 0; // Tijd sinds de laatste buzzer 
bool buzzerState = false; // Buzzer status voor komende piepjes

void buzzerOn(unsigned long now) {
  const unsigned long TICK = 250;
  if (now - lastBuzzerTime >= TICK) {
    buzzerState = !buzzerState;
    // if else statement die iedere TICK de buzzer aan of uit zet
    digitalWrite(BUZZER, buzzerState ? HIGH : LOW); 
    lastBuzzerTime = now;
  }
}

void buzzerOff() {
  digitalWrite(BUZZER, LOW);
}

int tickStep = 0; // 0-2 piepjes aan, 3 piepje uit

// Serial prints omdat mijn buzzer mogelijk niet werkt met deze methode,
// elders werkt het wel zoals tinkercad
void threeTicks(unsigned long now) {
  const unsigned long TICK = 750;
  const unsigned long NUMBER_OF_TICKS = 3;
  const unsigned long SEQUENCE_LENGTH = 4;
  if (tickStep < NUMBER_OF_TICKS) { // 3 piepjes
    if (now - lastBuzzerTime >= TICK) {
      buzzerState = true;
      digitalWrite(BUZZER, HIGH);
      lastBuzzerTime = now;
      tickStep++;
      Serial.println("Tick ON: " + String(tickStep));
    }
  } else if (tickStep < SEQUENCE_LENGTH) { // 1 piepje uit
    if (now - lastBuzzerTime >= TICK) {
      buzzerState = false;
      digitalWrite(BUZZER, LOW);
      lastBuzzerTime = now;
      tickStep++;
      Serial.println("Tick OFF: Silent");
    }
  } else {
    tickStep = 0;
    Serial.println("Resetting tickStep.");
  }
}

// Update met gebruik van tone
