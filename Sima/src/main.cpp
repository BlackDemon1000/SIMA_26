#include <Arduino.h>
#include <SCServo.h>

SMS_STS st;

const int right = 4;
const int left  = 5;

void setup() {
  Serial.begin(1000000); 
  st.pSerial = &Serial;  
  delay(1000);

  st.WheelMode(right);
  st.WheelMode(left);
}

void loop() {
  st.WriteSpe(right, 2200, 0);
  st.WriteSpe(left, 2200, 0);
  while(1);
}
