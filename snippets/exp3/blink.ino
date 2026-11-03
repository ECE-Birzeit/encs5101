// blink.ino: LED on pin 13 on for 1 s, off for 1 s, forever

const int LED_PIN = 13;           // also the on-board "L" LED
const int DELAY_MS = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);    // LED on
  delay(DELAY_MS);
  digitalWrite(LED_PIN, LOW);     // LED off
  delay(DELAY_MS);
}
