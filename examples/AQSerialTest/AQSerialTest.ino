#include <AquaControllerSerial.h>

AquaControllerSerial aq2(Serial1);

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);
}

void loop() {
  Serial.println(aq2.getTime());
  Serial.println(aq2.getPh());
  Serial.println(aq2.getOrp());
  Serial.println(aq2.getTemp());
  delay(1000);
}