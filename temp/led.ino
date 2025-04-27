const int redNorth = A0;
const int yellowNorth = A1;
const int greenNorth = A2;
const int redSouth = A3;
const int yellowSouth = A4;
const int greenSouth = A5;

unsigned long previousMillis = 0;
const long interval = 1000;

int ledState = 0;

void setup() {
  pinMode(redNorth, OUTPUT);
  pinMode(yellowNorth, OUTPUT);
  pinMode(greenNorth, OUTPUT);
  pinMode(redSouth, OUTPUT);
  pinMode(yellowSouth, OUTPUT);
  pinMode(greenSouth, OUTPUT);

  digitalWrite(redNorth, LOW);
  digitalWrite(yellowNorth, LOW);
  digitalWrite(greenNorth, LOW);
  digitalWrite(redSouth, LOW);
  digitalWrite(yellowSouth, LOW);
  digitalWrite(greenSouth, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    digitalWrite(redNorth, LOW);
    digitalWrite(yellowNorth, LOW);
    digitalWrite(greenNorth, LOW);
    digitalWrite(redSouth, LOW);
    digitalWrite(yellowSouth, LOW);
    digitalWrite(greenSouth, LOW);

    if (ledState == 0) {
      digitalWrite(redNorth, HIGH);  // Red North ON
    } else if (ledState == 1) {
      digitalWrite(yellowNorth, HIGH);  // Yellow North ON
    } else if (ledState == 2) {
      digitalWrite(greenNorth, HIGH);  // Green North ON
    } else if (ledState == 3) {
      digitalWrite(redSouth, HIGH);  // Red South ON
    } else if (ledState == 4) {
      digitalWrite(yellowSouth, HIGH);  // Yellow South ON
    } else if (ledState == 5) {
      digitalWrite(greenSouth, HIGH);  // Green South ON
    }

    ledState++;
    if (ledState > 5) {
      ledState = 0;
    }
  }
}

