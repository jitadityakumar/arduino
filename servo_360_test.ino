/*
Test 360 servo motor
1. Make motor turn clockwise 180 and then stop
2. Make motor turn anti clockwise 180 and then stop
*/

#include <Servo.h>
Servo myservo;

const int ledPin =  12;

int degrees = 180;
int run_num = 0;
int run_tot = 1;

void setup() {
  // servo pin
  myservo.attach(9);
  // LED Pin
  pinMode(ledPin, OUTPUT);
}

void motor (int val) {
  myservo.write(val);
}

void motor_ac (int d) {
  // empty for now
}

void run_motor() {
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
  motor(80);
  delay(5000);
  motor(90);
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
  motor(100);
  delay(5000);
  motor(90);
}

void loop() {
  if (run_num != run_tot) {
    run_motor();
    run_num += 1;
  }
}
