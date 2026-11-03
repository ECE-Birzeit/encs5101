// button.ino: LED on pin 13 follows a push button on pin 4
// (button to 5V, 10 kΩ pull-down from pin 4 to GND)

const int BUTTON_PIN = 4;
const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);     // the external resistor sets the idle level
}

void loop() {
  int state = digitalRead(BUTTON_PIN);   // HIGH while pressed, LOW when released
  digitalWrite(LED_PIN, state);
}
