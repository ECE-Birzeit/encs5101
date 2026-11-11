// lab2-starter.ino: Lab work 2. Fill in the three TODOs.
// TMP36 output on A0, LED on pin 8 through 220 Ω.

const int LED_PIN = 8;
const float T_ON = 0;             // TODO 1: your room temperature + 2 (°C)

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(A0);
  float volts = reading * 5.0 / 1023;
  float celsius = 0;              // TODO 2: convert volts to °C

  Serial.print(celsius);
  Serial.println(" C");

  // TODO 3: turn the LED on if celsius is above T_ON, off if it is not

  delay(1000);
}
