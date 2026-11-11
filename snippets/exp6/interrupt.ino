// interrupt.ino: count button presses with an external interrupt on pin 2
// Button between pin 2 and GND, internal pull-up.

const int BUTTON_PIN = 2;          // interrupt-capable: 2, 3, 18, 19, 20, 21
const int LED_PIN = 13;

volatile unsigned int presses = 0; // changed by the ISR, read by loop()

void onPress() {
  presses++;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onPress, FALLING);
  Serial.begin(9600);
}

void loop() {
  static unsigned int shown = 0;
  noInterrupts();                  // copy the shared variable in one piece
  unsigned int now = presses;
  interrupts();

  if (now != shown) {
    shown = now;
    Serial.println(now);
    digitalWrite(LED_PIN, now % 2); // LED toggles on each press
  }
}
