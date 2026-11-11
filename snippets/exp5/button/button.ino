// button.ino: the LED on pin 13 is on while the button on pin 4 is held.

extern "C" {
  void start();
  void update();
}

void setup() {
  start();
}

void loop() {
  update();             // read the button once and set the LED
}
