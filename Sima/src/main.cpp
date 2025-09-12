#include <Arduino.h>
#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial.begin(1000000);   
  sc.pSerial = &Serial;    

  delay(1000);
}

void loop()
{
  sc.WritePos(0xfe, 1000, 0, 1500);
  delay(754);

  sc.WritePos(0xfe, 20, 0, 1500);
  delay(754);
}

