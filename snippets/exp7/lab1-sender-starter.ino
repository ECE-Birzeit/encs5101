// lab1-sender-starter.ino: Lab work 1, board A. Fill in TODO 1 and TODO 2.
// Button between pin 2 and GND. Serial1 wired to board B as in Example 1.

const int BUTTON_PIN = 2;
bool wasPressed = false;           // the button state the last time round

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  // TODO 1: start Serial1 at 9600 baud
}

void loop() {
  bool pressed = (digitalRead(BUTTON_PIN) == LOW);   // LOW means pressed (pull-up)

  if (pressed != wasPressed) {     // the button has just been pressed or released
    wasPressed = pressed;
    if (pressed) {
      // TODO 2: send the character '1' to board B
      Serial.println("Sent 1");
    } else {
      Serial1.write('0');          // released: send '0'
      Serial.println("Sent 0");
    }
    delay(20);                     // let the contacts stop bouncing
  }
}
