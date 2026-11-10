// hbridge.ino: run a DC motor forward, stop, reverse, stop, through an L298N
// ENA on a PWM pin sets the speed, IN1/IN2 set the direction.

const int ENA = 10;   // PWM: speed
const int IN1 = 8;    // direction
const int IN2 = 9;

// speed from -255 (full reverse) through 0 (stop) to 255 (full forward)
void setMotor(int speed) {
  speed = constrain(speed, -255, 255);
  digitalWrite(IN1, speed > 0 ? HIGH : LOW);
  digitalWrite(IN2, speed < 0 ? HIGH : LOW);
  analogWrite(ENA, abs(speed));
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  setMotor(0);
}

void loop() {
  setMotor(200);    // forward
  delay(2000);
  setMotor(0);      // stop
  delay(1000);
  setMotor(-200);   // reverse
  delay(2000);
  setMotor(0);
  delay(1000);
}
