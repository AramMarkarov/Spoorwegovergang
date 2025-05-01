#include <Servo.h>

Servo barrierServo;

const int OPEN_ANGLE = 90;
const int CLOSED_ANGLE = 0;

bool barrierIsOpen = false;
bool barrierIsMoving = false;
unsigned long barrierMoveStartTime = 0;
const unsigned long SERVO_MOVE_DURATION = 2000;
unsigned long stateStartTime = 0;

void setupBarrier() {
  barrierServo.attach(SERVO);
}

void openBarrier() {
  barrierServo.write(OPEN_ANGLE);
  barrierIsOpen = true;
  barrierIsMoving = true;
  barrierMoveStartTime = millis();
}

void closeBarrier() {
  barrierServo.write(CLOSED_ANGLE);
  barrierIsOpen = false;
  barrierIsMoving = true;
  barrierMoveStartTime = millis();
}

void updateBarrierMovement(unsigned long now) {
  if (barrierIsMoving && now - barrierMoveStartTime >= SERVO_MOVE_DURATION) {
    barrierIsMoving = false;
    barrierIsOpen = (barrierServo.read() == OPEN_ANGLE);
  }
}
