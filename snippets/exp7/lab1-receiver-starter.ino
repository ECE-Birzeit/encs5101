// lab1-receiver-starter.ino: Lab work 1, board B. Fill in TODO 3 and TODO 4.
// LED on pin 8 through 220 ohm. Serial1 wired to board A as in Example 1.

const int LED_PIN = 8;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available() > 0) {
    char c = 0;                    // TODO 3: read one character from Serial1 into c

    Serial.print("Got ");
    Serial.println(c);

    // TODO 4: if c is '1' turn the LED on; if c is '0' turn it off
  }
}
