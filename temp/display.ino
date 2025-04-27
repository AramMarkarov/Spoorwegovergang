const int redNorth = A0;
const int yellowNorth = A1;
const int greenNorth = A2;
const int redSouth = A3;
const int yellowSouth = A4;
const int greenSouth = A5;

const int sensorWest = 7;
const int sensorEast = 4;
const int buttonNorth = 6;
const int buttonSouth = 5;

const int buzzer = 3;

const int dataPin  = 8;
const int latchPin = 9;
const int clockPin = 10;

const byte digits[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
 pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
 pinMode(dataPin, OUTPUT);
 displayDigit(4);

}

void loop() {}

void displayDigit(int number) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digits[number]);
  digitalWrite(latchPin, HIGH);
  Serial.print(digits[number]);
}
