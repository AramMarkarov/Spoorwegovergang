// Reset methode om de barrierMovement counter te resetten
void reset() {
if (Serial.available()) {
    char input = Serial.read();
    if (input == 'r') {
      barrierMovement = 0;
      Serial.println("Barrier movement counter reset to 0");
    }
  }
}
