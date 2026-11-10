// ramp.ino: sweep the PWM value 0 -> 255 and print it, to find where the motor starts turning
// Same wiring as hbridge.ino.

const int ENA = 10;
const int IN1 = 8;
const int IN2 = 9;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH);   // forward
  digitalWrite(IN2, LOW);
  Serial.begin(9600);
}

void loop() {
  for (int pwm = 0; pwm <= 255; pwm += 15) {
    analogWrite(ENA, pwm);
    Serial.print("PWM ");
    Serial.print(pwm);
    Serial.print("  duty ");
    Serial.print(pwm * 100L / 255);
    Serial.println(" %");
    delay(1000);
  }
  analogWrite(ENA, 0);
  delay(3000);
}
