const int OPEN_ANGLE = 90; // Simulatie van open en gesloten spoorboom
const int CLOSED_ANGLE = 70;
const unsigned long BARRIER_MOVE_TIME_MS = 16000; // Tijd voor het openen en sluiten van de spoorboom

bool barrierIsMoving = false;
bool barrierCount = false; // Om teller te activeren van de spoorboom
int barrierMovement = 0; // Teller hoe vaak de spoorboom is geopend

void openBarrier() {
  barrierServo.write(OPEN_ANGLE);
  barrierIsMoving = true;

  if (barrierCount) {
  barrierMovement++;
  Serial.print("Barrier moved ");
  Serial.print(barrierMovement);
  Serial.println(" times");
  barrierCount = false; // Stop met tellen na enkele beweiging
  } 
}

void closeBarrier() {
  barrierServo.write(CLOSED_ANGLE);
  barrierIsMoving = true;
}

// Implementeer een check voor servo closed en servo open
