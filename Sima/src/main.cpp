#include <Arduino.h>
#include <SCServo.h>

SCSCL sc;

void setup() {
  Serial.begin(1000000);
  sc.pSerial = &Serial;    
  delay(1000);

  sc.WritePos(4, 0, 0, 500);
  sc.WritePos(5, 0, 0, 500);
  delay(1000);
}

void loop() {
  int speed = 300;  // Positiv = vorwärts, Negativ = rückwärts
  sc.Run(4, speed, 0);  // Servo 4 läuft vorwärts
  sc.Run(5, -speed, 0); // Servo 5 läuft rückwärts  
  while(1); // nur einmal fahren
}
