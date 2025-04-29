void setup() {
  Serial.begin(9600);

  setupPins();
  setupTraffic();
  setupServo();
}

void loop() {
  handleButtonPress();
  updateTraffic();
  updateDisplayCounter();
  updateBuzzerDisplay();
}
