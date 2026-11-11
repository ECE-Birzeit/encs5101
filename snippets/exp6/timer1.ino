// timer1.ino: toggle the on-board LED every 0.25 s from a Timer1 overflow interrupt
// loop() is empty: the timer does all the work.

const int LED_PIN = 13;
const unsigned int PRELOAD = 49911;   // 65536 - 15625: overflows after 0.25 s at prescaler 256

void setup() {
  pinMode(LED_PIN, OUTPUT);

  noInterrupts();               // no interrupts while the timer is half set up
  TCCR1A = 0;                   // normal mode
  TCCR1B = 0;
  TCNT1 = PRELOAD;
  TCCR1B |= (1 << CS12);        // prescaler 256: this also starts the timer
  TIMSK1 |= (1 << TOIE1);       // enable the overflow interrupt
  interrupts();
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = PRELOAD;              // reload, or the next overflow takes 65536 counts
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void loop() {
  // free for other work
}
