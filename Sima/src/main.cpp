#include <Arduino.h>
#include <SCServo.h>

SMS_STS st;

const int right = 4;
const int left  = 5;

void setup() {
  Serial.begin(1000000);
  st.pSerial = &Serial;
  delay(1000);

}

void loop() {
  st.WriteSpe(right, 100, 0);
  st.WriteSpe(left, 100, 0);

  while(1); // nur einmal fahren
}
