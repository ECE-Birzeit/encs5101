// lab2.ino: Lab work 2. Nothing to change here; the TODOs are in asm.S.
// LED A on pin 25 (PA3), LED B on pin 27 (PA5), each through 220 ohm to GND.
// Button between pin 23 (PA1) and GND.

extern "C" {
  void start();
  void update();
}

void setup() {
  start();
}

void loop() {
  update();
}
