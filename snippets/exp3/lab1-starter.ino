// lab1-starter.ino: Lab work 1. Fill in the two TODOs.
// LEDs on pins 2, 3, 4 (each through 220 Ω to GND), button between pin 5 and GND.

const int LED_PINS[3] = {2, 3, 4};   // LED_PINS[0] shows bit 0, LED_PINS[1] bit 1, LED_PINS[2] bit 2
const int BUTTON_PIN = 5;

int count = 0;                       // 0..7
int last = HIGH;                     // the button reading on the previous pass

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int now = digitalRead(BUTTON_PIN);
  if (last == HIGH && now == LOW) {  // the button was just pressed
    // TODO 1: add 1 to count. After 7 it goes back to 0.
    delay(50);                       // ignore bounce
  }
  last = now;

  for (int i = 0; i < 3; i++) {
    // TODO 2: turn LED_PINS[i] on if bit i of count is 1, off if it is 0
  }
}
