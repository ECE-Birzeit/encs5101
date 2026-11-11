// ports.ino: blink a "7" on a common-cathode 7-segment, using port registers only
// Segments a..g on PORTA bits 0..6 = pins 22..28. Common pin to GND.

void setup() {
  DDRA = 0xFF;            // all 8 pins of port A are outputs
}

void loop() {
  PORTA = 0b00000111;     // segments a, b, c on: a "7"
  delay(1000);
  PORTA = 0x00;           // all segments off
  delay(1000);
}
