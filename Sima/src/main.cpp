#include <Arduino.h>
#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial.begin(1000000);   
  sc.pSerial = &Serial;    
  delay(1000);
}

void moveAndCheck(uint8_t id, int ziel)
{
  sc.WritePos(id, ziel, 0, 1500);
  delay(754); //temp

  int ist = sc.ReadPos(id);
  Serial.print("Servo ");
  Serial.print(id);
  Serial.print(" Ziel: ");
  Serial.print(ziel);
  Serial.print(" Ist: ");
  Serial.println(ist);

  //Nachregeln
  if (abs(ist - ziel) > 10) { // tol anpassen
    Serial.println("Abweichung erkannt, nachregeln...");
    sc.WritePos(id, ziel, 0, 1500);
  }
}

void loop()
{
  moveAndCheck(4, 1000);
  moveAndCheck(5, 20);
  delay(1000);
}

