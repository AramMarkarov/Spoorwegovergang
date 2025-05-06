void setup() {
  Serial.begin(9600);
  setupPins();
  setupTraffic();
}

void loop() {
  handleButtonPress();
  handleTrainDetection();
  updateTraffic();
  reset();
}
