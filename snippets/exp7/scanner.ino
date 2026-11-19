// scanner.ino: list the address of every device on the I2C bus.
// LCD backpack: GND -> GND, VCC -> 5V, SDA -> pin 20, SCL -> pin 21.

#include <Wire.h>

void setup() {
  Wire.begin();          // join the bus as the master
  Serial.begin(9600);
}

void loop() {
  int found = 0;
  Serial.println("Scanning...");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);   // START, then the address
    if (Wire.endTransmission() == 0) { // 0: a device answered with ACK
      Serial.print("Device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      found++;
    }
  }

  if (found == 0) Serial.println("No devices found");
  delay(5000);
}
