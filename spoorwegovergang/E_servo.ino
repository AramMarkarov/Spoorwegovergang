const int OPEN_ANGLE = 120;
const int CLOSED_ANGLE = 150;
const unsigned long BARRIER_MOVE_TIME_MS = 16000;

bool barrierIsMoving = false;

void openBarrier() {
  barrierServo.write(OPEN_ANGLE);
  barrierIsMoving = true;
}

void closeBarrier() {
  barrierServo.write(CLOSED_ANGLE);
  barrierIsMoving = true;
}
