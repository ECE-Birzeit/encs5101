// receiver.ino: board B. Pass everything that arrives on Serial1 on to the Serial Monitor.
// Wired to board A as in sender.ino.

void setup() {
  Serial.begin(9600);    // USB: this board's Serial Monitor
  Serial1.begin(9600);   // pins 18/19: the link to board A
}

void loop() {
  if (Serial1.available() > 0) {   // a byte has arrived from board A
    char c = Serial1.read();       // take it out of the receive buffer
    Serial.write(c);               // and show it, unchanged
  }
}
