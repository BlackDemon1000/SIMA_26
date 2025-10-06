#include <Arduino.h>
#include <SCServo.h>

SCSCL sc;

void setup() {
  Serial.begin(1000000);   
  sc.pSerial = &Serial;    
  delay(1000);
}

void loop() {
  // Positionen berechnet für 1 Meter Fahrt
  long posLinks  = 13020;  // Servo 4
  long posRechts = -13020; // Servo 5

  sc.WritePos(4, posLinks, 0, 1500);   // linker Motor
  sc.WritePos(5, posRechts, 0, 1500);  // rechter Motor

  while(1); // einmal fahren, dann stoppen
}
