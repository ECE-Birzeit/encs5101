// lab1-starter.ino: Lab work 1. Fill in the four TODOs; everything else is done for you.
// 7-segment on pins 22..28 (as in Example 1), button between pin 2 and GND.

const byte digits[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const int BUTTON_PIN = 2;
const unsigned int PRELOAD = 0;   // TODO 1: the preload for 1 second at prescaler 256

volatile byte count = 0;          // the digit on the display
volatile bool paused = false;     // true while the count is stopped

void onPress() {                  // runs on every button press
  static unsigned long last = 0;
  if (millis() - last < 200) return;   // a second "press" within 200 ms is bounce: ignore it
  last = millis();
  // TODO 4: flip paused (true becomes false, false becomes true)
}

void setup() {
  DDRA = 0xFF;                    // port A: all outputs
  PORTA = digits[0];              // show 0

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onPress, FALLING);

  noInterrupts();                 // Timer1 set up exactly as in Example 2
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = PRELOAD;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

ISR(TIMER1_OVF_vect) {            // runs once a second
  TCNT1 = PRELOAD;
  // TODO 2: if the count is not paused, add 1 to count. After 9 it goes back to 0.
  // TODO 3: show count on the display
}

void loop() {
  // nothing: the two interrupts do all the work
}
