#include <Servo.h>

Servo barrierServo;

const int OPEN_ANGLE = 90;
const int CLOSED_ANGLE = 0;

void setupServo() {
  barrierServo.attach(SERVO);
  closeBarrier();
}

void openBarrier() {
  barrierServo.write(OPEN_ANGLE);
}

void closeBarrier() {
  barrierServo.write(CLOSED_ANGLE);
}
