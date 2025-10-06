#include <Arduino.h>
#include <SCServo.h>

SCSCL sc;

void setup() {
  Serial.begin(1000000);
  sc.pSerial = &Serial;    
  delay(1000);

  // Servos auf aktuelle Position setzen, kleine Pause
  sc.WritePos(4, 0, 0, 500);
  sc.WritePos(5, 0, 0, 500);
  delay(1000);
}

void loop() {
  long posLinks  = 13020;  // 1 Meter
  long posRechts = -13020;

  sc.WritePos(4, posLinks, 0, 1500);
  sc.WritePos(5, posRechts, 0, 1500);

  while(1); // nur einmal fahren
}
