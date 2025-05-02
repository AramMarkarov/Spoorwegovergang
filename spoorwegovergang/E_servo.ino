const int OPEN_ANGLE = 90;
const int CLOSED_ANGLE = 70;
const unsigned long BARRIER_MOVE_TIME_MS = 16000;

bool barrierIsMoving;
unsigned long barrierMovementStartTime = 0;

void openBarrier(unsigned long now) {
  barrierServo.write(OPEN_ANGLE);
  barrierIsMoving = true;
  updateBarrierMovement(now);
}

void closeBarrier(unsigned long now) {
  barrierServo.write(CLOSED_ANGLE);
  barrierIsMoving = true;
  updateBarrierMovement(now);
}

void updateBarrierMovement(unsigned long now) {
  if (now - barrierMovementStartTime >= BARRIER_MOVE_TIME_MS) {
    barrierIsMoving = false;
  }

  if (barrierIsMoving) {
    buzzerOn(now);
  } else {
    buzzerOff();
    barrierMovementStartTime = now;
  }
}
