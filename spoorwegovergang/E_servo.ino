const int OPEN_ANGLE = 90;
const int CLOSED_ANGLE = 70;
const unsigned long BARRIER_MOVE_TIME_MS = 16000;

bool barrierIsMoving = false;
unsigned long barrierMovementStartTime = 0;

void openBarrier(unsigned long now) {
  barrierServo.write(OPEN_ANGLE);
  barrierIsMoving = true;
  barrierMovementStartTime = now;
}

void closeBarrier(unsigned long now) {
  barrierServo.write(CLOSED_ANGLE);
  barrierIsMoving = true;
  barrierMovementStartTime = now;
}

void updateBarrierMovement(unsigned long now) {
  Serial.print("barrierIsMoving: ");
  Serial.println(barrierIsMoving);
  Serial.print("now: ");
  Serial.print(now);
  Serial.print("  start: ");
  Serial.print(barrierMovementStartTime);
  Serial.print("  diff: ");
  Serial.println(now - barrierMovementStartTime);

  if (barrierIsMoving && (now - barrierMovementStartTime >= BARRIER_MOVE_TIME_MS)) {
    Serial.println("Barrier movement finished.");
    barrierIsMoving = false;
  }

  if (barrierIsMoving) {
    buzzerOn(now);
  } else {
    buzzerOff();
  }
}
