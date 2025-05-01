void setup() {
  Serial.begin(9600);

  setupPins();
  setupTraffic();
  setupBarrier();
  openBarrier();
}

void loop() {
  unsigned long now = millis();
  handleButtonPress();
  handleTrainDetection();
  updateTraffic();
  updateBarrierMovement(now);
  updateDisplayCounter();
  updateBuzzerDisplay();
}
