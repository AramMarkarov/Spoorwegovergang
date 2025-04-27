const int buzzerPin = 3; 
unsigned long previousMillis = 0;
const long buzzerOnTime = 2000;
const long buzzerOffTime = 3000;

bool buzzerState = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (buzzerState == false && currentMillis - previousMillis >= buzzerOffTime) {
    buzzerState = true;
    previousMillis = currentMillis;
    tone(buzzerPin, 1000);
  } else if (buzzerState == true && currentMillis - previousMillis >= buzzerOnTime) {
        buzzerState = false;
    previousMillis = currentMillis;
    noTone(buzzerPin);
  }
}

