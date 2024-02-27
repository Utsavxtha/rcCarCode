#include <AFMotor.h>

#define MAX 120
#define REDUCE 0.6
#define RIGHT_WT 1.15
#define RIGHT_DELAY 40


char state, prevState;
// RX, TX

//initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(3);


void setup() {
  Serial.begin(9600);
}

void loop() {

  state = Serial.read();

  if (Serial.available() > 0) {

    state = Serial.read();
    Serial.println(state);


    switch (state) {

      case 'F':
        runCar(MAX, MAX);
        break;

      case 'B':
        runCar(-MAX, -MAX);
        break;

      case 'L':
        runCar(-MAX, MAX);
        break;

      case 'R':
        runCar(MAX, -MAX);
        break;

      case 'G':
        runCar(MAX * REDUCE, MAX);
        break;

      case 'I':
        runCar(MAX, MAX * REDUCE);
        break;

      case 'H':
        runCar(-MAX * REDUCE, -MAX);
        break;

      case 'J':
        runCar(-MAX, -MAX * REDUCE);
        break;

      default:
        Stop();
        break;
    }
    // delay(1000);
    prevState = state;
  }
}

void runCar(int left, int right) {

  motor1.run(FORWARD);
  motor2.run(FORWARD);

  if (left < 0) {
    motor1.run(BACKWARD);
    left *= -1;
  }

  if (right < 0) {
    motor2.run(BACKWARD);
    right *= -1;
  }

  motor1.setSpeed(left);
  motor2.setSpeed(right * RIGHT_WT);
}

void Stop() {
  motor1.run(RELEASE);  //stop the motor when release  the button
  motor1.setSpeed(0);
  if (prevState != 'S')
    delay(RIGHT_DELAY);
  motor2.run(RELEASE);  //rotate the motor clockwise
  motor2.setSpeed(0);   //Define minimum velocity
}
