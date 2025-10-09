#include <Arduino.h>
#include <SCServo.h>

SMS_STS st;

const int right = 4;
const int left  = 5;

// --- Odometrie ---
const float wheelDiameterCm = 10.35; //hier länge tunen
const float wheelCircumference = 3.14159265358979323846 * wheelDiameterCm; 
const int TICKS_PER_REV = 4096; // 0..4095

// --- Regler-Parameter ---
const float Kp_sync = 3.0;     // Synchronisationsverstärkung 
const int   MAX_SPEED = 3000;  // obere Grenze
const int   MIN_SPEED = 200;   // untere Grenze (vermeidet Stillstand)

long cmToTicks(float cm) {
  float revs = cm / wheelCircumference;
  float ticks = revs * TICKS_PER_REV;
  return (long)(ticks + 0.5); // runden
}

void driveDistance(int cm, int baseSpeed) {
  long targetTicks = cmToTicks(cm);

  // Startpositionen
  long startPosRight = st.ReadPos(right);
  long startPosLeft  = st.ReadPos(left);
  long lastPosRight = startPosRight;
  long lastPosLeft  = startPosLeft;

  unsigned long posRightGes = 0;
  unsigned long posLeftGes  = 0;

  // Motoren starten
  st.WriteSpe(right, baseSpeed, 0);
  st.WriteSpe(left, -baseSpeed, 0); // evtl. Vorzeichen anpassen

  // Fahr-Schleife
  while (posRightGes < (unsigned long)targetTicks) {
    int newPosRight = st.ReadPos(right);
    int newPosLeft  = st.ReadPos(left);

    int deltaRight = newPosRight - lastPosRight;
    int deltaLeft  = newPosLeft - lastPosLeft;

    // Wrap-around Korrektur
    if (deltaRight > 2048) deltaRight -= 4096;
    if (deltaRight < -2048) deltaRight += 4096;
    if (deltaLeft > 2048)  deltaLeft  -= 4096;
    if (deltaLeft < -2048) deltaLeft  += 4096;

    posRightGes += abs(deltaRight);
    posLeftGes  += abs(deltaLeft);

    lastPosRight = newPosRight;
    lastPosLeft  = newPosLeft;

    // --- Synchronisations-Regler ---
    long diff = (long)posLeftGes - (long)posRightGes;  // positiv: links läuft voraus, negativ: rechts läuft voraus
    float adjust = Kp_sync * diff;

    int speedRight = baseSpeed + (int)adjust;
    int speedLeft  = baseSpeed - (int)adjust;

    // Begrenzen
    if (speedRight > MAX_SPEED) speedRight = MAX_SPEED;
    if (speedRight < MIN_SPEED) speedRight = MIN_SPEED;
    if (speedLeft > MAX_SPEED)  speedLeft  = MAX_SPEED;
    if (speedLeft < MIN_SPEED)  speedLeft  = MIN_SPEED;

    // Anwenden 
    st.WriteSpe(right, speedRight, 0);
    st.WriteSpe(left, -speedLeft, 0);

    delay(20);
  }

  // Stoppen
  st.WriteSpe(right, 0, 0);
  st.WriteSpe(left, 0, 0);
}

void setup() {
  Serial.begin(1000000); 
  st.pSerial = &Serial;  
  delay(1000);

  st.WheelMode(right);
  st.WheelMode(left);
}

void loop() {
  driveDistance(100, 2200);
  while (1) { delay(1000); }
}
