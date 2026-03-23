#include <SCServo.h>
SMS_STS st;

// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 18    //Customize the IO of the serial port, if you don't use the custom serial port below Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD); you need to change to Serial1.begin(1000000);.
#define S_TXD 19

byte ID[2];
s16 Position[2];
u16 Speed[2];
byte ACC[2];

void setup()
{
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  st.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;   // Save the servo ID to be controlled to ID[].
  ID[1] = 2;   //Save the servo ID to be controlled to ID[].
  Speed[0] = 3400;  // Set the servo speed, Speed[0] corresponds to the servo with ID[0] above.
  Speed[1] = 3400;  // Set the servo speed, Speed[1] corresponds to the servo with ID[1] above.
  ACC[0] = 50;   // Set the start/stop acceleration, the lower the value the lower the acceleration, and the maximum can be set to 150.
  ACC[1] = 50;
}

void loop()
{
  Position[0] = 3000;  // Set the target position of the servo with ID[0] (in this case ID 1) in the range 0-4095
  Position[1] = 3000;  // Set the target position of the servo with ID[1] (here with ID 2) in the range 0-4095
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servo(ID1/ID2) speed=3400，acc=50，move to position=3000.
  delay(2000);

  Position[0] = 100;
  Position[1] = 100;
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servo(ID1/ID2) speed=3400，acc=50，move to position=100.
  delay(2000);
}