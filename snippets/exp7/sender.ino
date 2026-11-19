// sender.ino: board A. Send a counter to board B over Serial1, once a second.
// Board A pin 18 (TX1) -> board B pin 19 (RX1), pin 19 -> pin 18, GND -> GND.

int count = 0;

void setup() {
  Serial.begin(9600);    // USB: this board's own Serial Monitor
  Serial1.begin(9600);   // pins 18/19: the link to board B. Same baud on both boards.
}

void loop() {
  Serial1.println(count);              // to board B
  Serial.print("Sent ");               // to our own monitor, so we can see it
  Serial.println(count);
  count++;
  delay(1000);
}
