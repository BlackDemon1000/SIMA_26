#include <Arduino.h>
#include <SCServo.h>

SMS_STS st;

const int right = 4;
const int left  = 5;

//Variablen für odometrie
const float wheelDiameterCm = 10.0;
const float wheelCircumference = 3.14159265358979323846 * wheelDiameterCm; // 31.4159265...
const int TICKS_PER_REV = 4096; // 0..4095

long cmToTicks(float cm) {
  float revs = cm / wheelCircumference;
  float ticks = revs * TICKS_PER_REV;
  return (long)(ticks + 0.5); // runden
}


void setup() {
  Serial.begin(1000000); 
  st.pSerial = &Serial;  
  delay(1000);

  st.WheelMode(right);
  st.WheelMode(left);
}

void loop() {
  // Ziel: 100 cm (1 Meter)
  long targetTicks = cmToTicks(100.0); // ergibt ~13038

  // Reset / Anfangspositionen
  long startPosRight = st.ReadPos(right);
  long startPosLeft  = st.ReadPos(left);
  long lastPosRight = startPosRight;
  long lastPosLeft  = startPosLeft;

  unsigned long posRightGes = 0;
  unsigned long posLeftGes  = 0;

  // Starte Motoren (Geschwindigkeit anpassen)
  int speedRight = 2000; // Beispielwerte, anpassen
  int speedLeft  = 2000;

  st.WriteSpe(right, speedRight, 0);
  st.WriteSpe(left, -speedLeft, 0); // ggf. Vorzeichen an Orientierung anpassen

  // Fahr-Schleife
  while (posRightGes < (unsigned long)targetTicks) {
    int newPosRight = st.ReadPos(right);
    int newPosLeft  = st.ReadPos(left);

    int deltaRight = newPosRight - lastPosRight;
    int deltaLeft  = newPosLeft - lastPosLeft;

    // Wrap-around Korrektur (Positionsbereich 0..4095 => Modulo 4096)
    if (deltaRight > 2048) deltaRight -= 4096;
    if (deltaRight < -2048) deltaRight += 4096;
    if (deltaLeft > 2048)  deltaLeft  -= 4096;
    if (deltaLeft < -2048) deltaLeft  += 4096;

    posRightGes += (unsigned long)abs(deltaRight);
    posLeftGes  += (unsigned long)abs(deltaLeft);

    lastPosRight = newPosRight;
    lastPosLeft  = newPosLeft;

    // kurz warten, nicht zu kurz (Entlastet Bus)
    delay(20);
  }

  // Stoppe Motoren
  st.WriteSpe(right, 0, 0);
  st.WriteSpe(left, 0, 0);

  // Ende: Lampe an
  digitalWrite(13, HIGH);

  // Einmal fahren: beenden
  while (1) { delay(1000); }
}
