// lab1.ino: Lab work 1. Nothing to change here; the TODOs are in asm.S.
// LED A on pin 22 (PA0), LED B on pin 23 (PA1), each through 220 ohm to GND.

extern "C" {
  void start();
  void show(byte which);
}

void setup() {
  start();
}

void loop() {
  show(0);              // LED A on, LED B off
  delay(1000);
  show(1);              // LED B on, LED A off
  delay(1000);
}
