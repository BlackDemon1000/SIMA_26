#include <Arduino.h>
#include "drive.h"

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
