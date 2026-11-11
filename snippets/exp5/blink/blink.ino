// blink.ino: the C side. It only calls the two assembly functions in asm.S.

extern "C" {            // these functions are written in assembly, in asm.S
  void start();
  void led(byte on);
}

void setup() {
  start();              // set pin 13 as an output
}

void loop() {
  led(1);               // on
  delay(200);
  led(0);               // off
  delay(200);
}
