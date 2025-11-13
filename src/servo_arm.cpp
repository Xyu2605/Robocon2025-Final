#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "servo_arm.h"

int angle1 = 0;
int angle2 = 110;
int angle3 = 145;
int angle4 = 0;
int angle5 = 0;
int angle6 = 0;
int defaultAngles[4] = {90, 80, 90, 20};
int takeTheBallAngles[4] = {0, 110, 125, 90};
int dropTheBallAngles[4] = {160, 90, 35, 90};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

static const int servoChannels[6] = { SERVO_1, SERVO_2, SERVO_3, SERVO_4, SERVO_5, SERVO_6 };

void updateArm(int id, int targetAngle) {

  targetAngle = constrain(targetAngle, 0, 180);
  int *currentAngle = nullptr;
  int servoChannel = 0;

  switch(id) {
    case 1: currentAngle = &angle1; servoChannel = SERVO_1; break;
    case 2: currentAngle = &angle2; servoChannel = SERVO_2; break;
    case 3: currentAngle = &angle3; servoChannel = SERVO_3; break;
    case 4: currentAngle = &angle4; servoChannel = SERVO_4; break;
    case 5: currentAngle = &angle5; servoChannel = SERVO_5; break;
    case 6: currentAngle = &angle6; servoChannel = SERVO_6; break;
    default: return;
  }
  
  int steps = abs(targetAngle - *currentAngle);
  int diff = targetAngle - *currentAngle;
  if (diff == 0) return;

  int stepSize = max(1, stepAngle);
  int stepsNeeded = (abs(diff) + stepSize - 1) / stepSize; 

  for (int step = 1; step <= stepsNeeded; step++) {
    int travelled = step * stepSize;
    if (travelled > abs(diff)) travelled = abs(diff);
    int intermediateAngle = *currentAngle + (diff > 0 ? travelled : -travelled);
    uint16_t pulse = map(intermediateAngle, 0, 180, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servoChannel, 0, pulse);
    delay(servoMoveSpeed);
  }
  *currentAngle = targetAngle;

  Serial.printf("Servo1: %d\tServo2: %d\tServo3: %d\tServo4: %d\tServo5: %d\tServo6: %d\n", angle1, angle2, angle3, angle4, angle5, angle6);
}

void autoUpdateArm(int targetAngles[], int numServos) {
  int currentAngles[4] = {angle1, angle2, angle3, angle4};
  int maxSteps = 0;

  int stepSize = max(1, stepAngle);
  for (int i = 0; i < numServos; i++) {
    int diff = abs(targetAngles[i] - currentAngles[i]);
    int stepsForServo = (diff + stepSize - 1) / stepSize; 
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

      pwm.setPWM(servoChannels[i], 0, pulse);
    }
    delay(servoMoveSpeed);
  }

  angle1 = targetAngles[0];
  angle2 = targetAngles[1];
  angle3 = targetAngles[2];
  angle4 = targetAngles[3];
}

void takeTheBall() { 
  Serial.println("Take the ball"); 
  autoUpdateArm(takeTheBallAngles, 3); 
}

void dropTheBall() {
  Serial.println("Drop the ball");
  updateArm(2,90);
  delay(200);
  updateArm(3, 35);
  delay(200);
  updateArm(1, 160);
  delay(200);
  updateArm(4,90);
  delay(200);
}

void setDefaultArm() { 
  Serial.println("Set default arm"); 
  autoUpdateArm(defaultAngles, 4); 
}


// void servoUp(int id) {
//   int angle = 0;
//   if (id == 1) angle = angle1;
//   else if (id == 2) angle = angle2;
//   else if (id == 3) angle = angle3;
//   else if (id == 4) angle = angle4;

//   updateArm(id, angle + stepAngle);
// }

void servoUp(int id) {
  updateArm(
    id,
    (id == 1 ? angle1 :
     id == 2 ? angle2 :
     id == 3 ? angle3 :
     angle4) + stepAngle
  );
}
void servoDown(int id) {
  updateArm(
    id,
    (id == 1 ? angle1 :
     id == 2 ? angle2 :
     id == 3 ? angle3 :
     angle4) - stepAngle
  );
}

void handleCommandServo(char cmd){
    switch(cmd){
    case 'Q': servoUp(1); break;
    case 'A': servoDown(1); break;
    case 'W': servoUp(2); break;
    case 'X': servoDown(2); break;
    case 'D': servoUp(3); break;
    case 'E': servoDown(3); break;
    case 'O': servoUp(4); break;
    case 'P': servoDown(4); break;
    case 'Z': takeTheBall(); break;
    case 'N': dropTheBall(); break;
    case '+': updateArm(5, angle5 + 90); break;
    case '-': updateArm(5, angle5 - 90); break;
    case '8': updateArm(6, angle6 + 65); break;
    case '9': updateArm(6, angle6 - 65); break;
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
