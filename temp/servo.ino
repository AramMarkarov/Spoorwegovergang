#include <Servo.h>

const int servoPin = 2;

Servo servo;

unsigned long previousMillis = 0;
const long interval = 15;

int servoPos = 0;
int targetPos = 180;

void setup() {
  servo.attach(servoPin);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (servoPos < targetPos) {
      servoPos++;
    } else if (servoPos > targetPos) {
      servoPos--;
    }

    servo.write(servoPos);
  }

  if (servoPos == targetPos) {
    targetPos = (targetPos == 180) ? 0 : 180;
  }
}

