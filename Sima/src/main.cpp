#include <Arduino.h>
#include <SCServo.h>

SMS_STS st;

// ESP32 NodeMCU V2 – Serial1 Pins (frei wählbar)
// Waveshare Board: TX → GPIO16 (RX1), RX → GPIO17 (TX1)
#define S_RXD 16
#define S_TXD 17

const int LED = 2; // Onboard LED ESP32 NodeMCU V2

int foundIDs[20];
int foundCount = 0;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(115200);       // Monitor über USB
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD); // Servo-Bus
  st.pSerial = &Serial1;
  delay(1000);

  Serial.println("=== Servo Scan gestartet ===");

  for (int id = 1; id <= 253; id++) {
    int found = st.Ping(id);
    if (found != -1) {
      foundIDs[foundCount++] = found;
      Serial.print(">>> Motor gefunden! ID: ");
      Serial.println(found);
    }
    delay(10);
  }

  Serial.println("=== Scan abgeschlossen ===");

  if (foundCount == 0) {
    Serial.println("Keine Motoren gefunden! Verkabelung pruefen.");
    // Schnelles Blinken
    for (int i = 0; i < 20; i++) {
      digitalWrite(LED, HIGH); delay(100);
      digitalWrite(LED, LOW);  delay(100);
    }
  } else {
    Serial.print("Gefunden: ");
    Serial.print(foundCount);
    Serial.println(" Motor(en)");

    // LED an
    digitalWrite(LED, HIGH);

    // Wheel-Mode + drehen
    for (int i = 0; i < foundCount; i++) {
      int id = foundIDs[i];
      Serial.print("Starte Motor ID: ");
      Serial.println(id);
      st.WheelMode(id);
      delay(50);
      st.WriteSpe(id, 1000, 0);
    }
  }
}

void loop() {
  // Motoren laufen bis Reset
}