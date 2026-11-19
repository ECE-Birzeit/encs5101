// lab2-slave-starter.ino: Lab work 2, the slave board. Fill in TODO 1.
// Potentiometer: ends to 5V and GND, wiper to A0. SDA, SCL and GND wired to the master.

#include <Wire.h>

const byte MY_ADDRESS = 8;         // this board's I2C address

void onRequest() {                 // runs when the master asks for data
  int reading = analogRead(A0);    // 0..1023: needs 10 bits, too big for one byte
  // TODO 1: send reading as two bytes, the high byte first, then the low byte
}

void setup() {
  Wire.begin(MY_ADDRESS);          // join the bus as a slave at this address
  Wire.onRequest(onRequest);       // call onRequest() on every request
}

void loop() {
  // nothing: onRequest() does all the work
}
