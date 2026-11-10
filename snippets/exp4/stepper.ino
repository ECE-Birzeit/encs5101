// stepper.ino: one revolution clockwise, then one counterclockwise
// 28BYJ-48 stepper on a ULN2003 board: IN1..IN4 to pins 8..11.

#include <Stepper.h>

const int STEPS_PER_REV = 2048;   // 28BYJ-48 in full-step mode, after its gearbox

// Note the order 8, 10, 9, 11: the library wants IN1, IN3, IN2, IN4.
Stepper motor(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  motor.setSpeed(10);   // rpm; the 28BYJ-48 tops out around 15
  Serial.begin(9600);
}

void loop() {
  Serial.println("clockwise");
  motor.step(STEPS_PER_REV);     // blocks until the revolution is done
  delay(500);

  Serial.println("counterclockwise");
  motor.step(-STEPS_PER_REV);
  delay(500);
}
