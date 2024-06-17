#include <SpeedControlServo.h>

const int SERVO_PIN = 15;
SpeedControlServo servo;

void setup() {
  // Initialize
  servo.attach(SERVO_PIN);
}

void loop() {
  // Move to 0deg in 200ms
  servo.write(200, 0);
  delay(2000);

  // Move to 0deg in 1000ms
  servo.write(1000, 180);
  delay(2000);
}

void loop1() {
  // Loop Process
  servo.loopProcess();
}