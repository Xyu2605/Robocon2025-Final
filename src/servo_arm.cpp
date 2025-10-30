#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "servo_arm.h"

int angle1 = 0;
int angle2 = 110;
int angle3 = 145;
int defaultAngles[3] = {0, 80, 120};
int takeTheBallAngles[3]    = {0, 110, 125};
int dropTheBallAngles[3] = {90, 110, 145};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

static const int servoChannels[3] = { SERVO_1, SERVO_2, SERVO_3 };

void updateArm(int id, int targetAngle) {

  targetAngle = constrain(targetAngle, 0, 180);
  int *currentAngle = nullptr;
  int servoChannel = 0;

  switch(id) {
    case 1: currentAngle = &angle1; servoChannel = SERVO_1; break;
    case 2: currentAngle = &angle2; servoChannel = SERVO_2; break;
    case 3: currentAngle = &angle3; servoChannel = SERVO_3; break;
    default: return;
  }

  int steps = abs(targetAngle - *currentAngle);
  int diff = targetAngle - *currentAngle;
  if (diff == 0) return;

  int stepSize = max(1, stepAngle);
  int stepsNeeded = (abs(diff) + stepSize - 1) / stepSize; // ceil division

  for (int step = 1; step <= stepsNeeded; step++) {
    int travelled = step * stepSize;
    if (travelled > abs(diff)) travelled = abs(diff);
    int intermediateAngle = *currentAngle + (diff > 0 ? travelled : -travelled);
    uint16_t pulse = map(intermediateAngle, 0, 180, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servoChannel, 0, pulse);
    delay(servoMoveSpeed);
  }
  *currentAngle = targetAngle;
}

void autoUpdateArm(int targetAngles[], int numServos) {
  int currentAngles[3] = {angle1, angle2, angle3};
  int maxSteps = 0;

  // Determine how many steps are needed using the configured stepAngle
  int stepSize = max(1, stepAngle);
  for (int i = 0; i < numServos; i++) {
    int diff = abs(targetAngles[i] - currentAngles[i]);
    int stepsForServo = (diff + stepSize - 1) / stepSize; // ceil
    if (stepsForServo > maxSteps) maxSteps = stepsForServo;
  }
  if (maxSteps == 0) return;

  for (int step = 1; step <= maxSteps; step++) {
    for (int i = 0; i < numServos; i++) {
      int diff = targetAngles[i] - currentAngles[i];
      int travelled = step * stepSize;
      if (travelled > abs(diff)) travelled = abs(diff);
      int intermediateAngle = currentAngles[i] + (diff > 0 ? travelled : -travelled);
      uint16_t pulse = map(intermediateAngle, 0, 180, SERVO_MIN, SERVO_MAX);
      // use explicit servo channel mapping
      pwm.setPWM(servoChannels[i], 0, pulse);
    }
    delay(servoMoveSpeed);
  }

  // update globals
  angle1 = targetAngles[0];
  angle2 = targetAngles[1];
  angle3 = targetAngles[2];
}

void takeTheBall() { 
  Serial.println("Take the ball"); 
  autoUpdateArm(takeTheBallAngles, 3); 
}

void dropTheBall() {
  Serial.println("Drop the ball"); 
  autoUpdateArm(dropTheBallAngles, 3); 
}

void setDefaultArm() { 
  Serial.println("Set default arm"); 
  autoUpdateArm(defaultAngles, 3); 
}

void servoUp(int id) { updateArm(id, (id==1?angle1:(id==2?angle2:angle3)) + stepAngle); }
void servoDown(int id) { updateArm(id, (id==1?angle1:(id==2?angle2:angle3)) - stepAngle); }

void handleCommandServo(char cmd){
    switch(cmd){
    case 'Q': servoUp(1); break;
    case 'A': servoDown(1); break;
    case 'W': servoUp(2); break;
    case 'X': servoDown(2); break;
    case 'E': servoUp(3); break;
    case 'D': servoDown(3); break;
    case 'Z': takeTheBall(); break;
    case 'N': dropTheBall(); break;
    default : break;
  }
} 

void initServo() {
  Wire.begin(SDA_PIN, SCL_PIN);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);
  setDefaultArm();
  Serial.println("Servo initialized!");
}
