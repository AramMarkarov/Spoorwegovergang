#include <Servo.h>

// Knoppen en sensoren
const int SENSOREAST = 4;
const int BUTTONNORTH = 5;
const int BUTTONSOUTH = 6;
const int SENSORWEST = 7;

// Buzzer
const int BUZZER = 3;

// Servo
const int SERVO = 13;

// Verkeerslichten Noord (A0-A2)
const int RED_NORTH = A2;
const int YELLOW_NORTH = A1;
const int GREEN_NORTH = A0;

// Verkeerslichten Zuid (A3-A5)
const int RED_SOUTH = A5;
const int YELLOW_SOUTH = A4;
const int GREEN_SOUTH = A3;

// Shift register (7-segment)
const int SHIFT_DATA = 8;
const int SHIFT_LATCH = 9;
const int SHIFT_CLOCK = 10;

// Display
const int DATAPIN  = 8;
const int LATCHPIN = 9;
const int CLOCKPIN = 10;

Servo barrierServo;

void setupPins() {
  // Knoppen en sensoren
  pinMode(SENSOREAST, INPUT);
  pinMode(BUTTONSOUTH, INPUT);
  pinMode(BUTTONNORTH, INPUT);
  pinMode(SENSORWEST, INPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  barrierServo.attach(SERVO);

  // LED’s
  pinMode(RED_NORTH, OUTPUT);
  pinMode(YELLOW_NORTH, OUTPUT);
  pinMode(GREEN_NORTH, OUTPUT);
  pinMode(RED_SOUTH, OUTPUT);
  pinMode(YELLOW_SOUTH, OUTPUT);
  pinMode(GREEN_SOUTH, OUTPUT);

  // Shift register
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  pinMode(SHIFT_CLOCK, OUTPUT);

  // Display
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(DATAPIN, OUTPUT);
}   
