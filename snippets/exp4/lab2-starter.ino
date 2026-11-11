// lab2-starter.ino: Lab work 2. Fill in the two TODOs.
// 28BYJ-48 on a ULN2003 board wired as in Example 3. Serial Monitor at 9600 baud, line ending "Newline".

#include <Stepper.h>

const int STEPS_PER_REV = 2048;
Stepper motor(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  motor.setSpeed(10);
  Serial.begin(9600);
  Serial.println("Type an angle in degrees (negative turns the other way):");
}

void loop() {
  if (Serial.available() > 0) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    int angle = line.toInt();

    long steps = 0;   // TODO 1: convert angle to steps
    // TODO 2: move the motor by that many steps

    Serial.print("Turned ");
    Serial.print(angle);
    Serial.println(" degrees");
  }
}
