// lab1-starter.ino: Lab work 1. Fill in the two TODOs.
// L298N wired as in Example 1. Serial Monitor at 9600 baud, line ending "Newline".

const int ENA = 10;
const int IN1 = 8;
const int IN2 = 9;

// setMotor() from Example 1: -255 full reverse, 0 stop, 255 full forward
void setMotor(int speed) {
  digitalWrite(IN1, speed > 0 ? HIGH : LOW);
  digitalWrite(IN2, speed < 0 ? HIGH : LOW);
  analogWrite(ENA, abs(speed));
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  setMotor(0);
  Serial.begin(9600);
  Serial.println("Type a speed from -255 to 255:");
}

void loop() {
  if (Serial.available() > 0) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    int speed = line.toInt();

    // TODO 1: if speed is from -255 to 255, call setMotor(speed) and print "Speed set to " and the speed
    // TODO 2: otherwise print "Out of range: use -255 to 255" and leave the motor as it is
  }
}
