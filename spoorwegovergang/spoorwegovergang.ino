void setup() {
  Serial.begin(9600);

  setupPins();  // methode met alle pinmode()
  setupTrafficLights();
}

void loop() {
  handleButtonPress();
  updateTrafficLights();
  
}

