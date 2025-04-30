void setup() {
  Serial.begin(9600);

  setupPins();
  setupTraffic();
  setupBarrier();
  openBarrier();
}

void loop() {
  handleButtonPress();
  updateTraffic();
  loopBarrier();
  updateDisplayCounter();
  updateBuzzerDisplay();
}
