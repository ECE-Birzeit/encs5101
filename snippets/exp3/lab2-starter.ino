// lab2-starter.ino: Lab work 2. Fill in the two TODOs.
// LED on pin 13 (the on-board one is enough), buttons between pin 6 / pin 7 and GND.

const int LED_PIN = 13;
const int FASTER_PIN = 6;
const int SLOWER_PIN = 7;

unsigned long interval = 500;        // ms between toggles
unsigned long lastToggle = 0;
int lastFaster = HIGH;
int lastSlower = HIGH;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(FASTER_PIN, INPUT_PULLUP);
  pinMode(SLOWER_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Blink without delay(), so the buttons are read on every pass
  if (millis() - lastToggle >= interval) {
    lastToggle = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }

  int faster = digitalRead(FASTER_PIN);
  if (lastFaster == HIGH && faster == LOW) {
    // TODO 1: make interval 100 shorter, but never below 100
    Serial.println(interval);
    delay(50);
  }
  lastFaster = faster;

  int slower = digitalRead(SLOWER_PIN);
  if (lastSlower == HIGH && slower == LOW) {
    // TODO 2: make interval 100 longer, but never above 1000
    Serial.println(interval);
    delay(50);
  }
  lastSlower = slower;
}
