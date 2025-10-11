#include <Arduino.h>
#include "robot.h"

void setMotor(int in1, int in2, int channel, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    ledcWrite(channel, speed);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    ledcWrite(channel, -speed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    ledcWrite(channel, 0);
  }
}

void motorSpin(int v1, int v2, int v3, int v4) {
  v1 = constrain(v1, -255, 255);
  v2 = constrain(v2, -255, 255);
  v3 = constrain(v3, -255, 255);
  v4 = constrain(v4, -255, 255);

  setMotor(IN1_1, IN2_1, PWM_CHANNEL_0, v1); // Motor 1 - Trước trái
  setMotor(IN3_1, IN4_1, PWM_CHANNEL_1, v2); // Motor 2 - Trước phải
  setMotor(IN1_2, IN2_2, PWM_CHANNEL_2, v3); // Motor 3 - Sau trái
  setMotor(IN3_2, IN4_2, PWM_CHANNEL_3, v4); // Motor 4 - Sau phải
}

void initRobot() {

  pinMode(IN1_1, OUTPUT);
  pinMode(IN2_1, OUTPUT);
  pinMode(IN3_1, OUTPUT);
  pinMode(IN4_1, OUTPUT);

  pinMode(IN1_2, OUTPUT);
  pinMode(IN2_2, OUTPUT);
  pinMode(IN3_2, OUTPUT);
  pinMode(IN4_2, OUTPUT);

  // Cấu hình PWM cho 4 kênh
  ledcSetup(PWM_CHANNEL_0, freq, resolution);
  ledcSetup(PWM_CHANNEL_1, freq, resolution);
  ledcSetup(PWM_CHANNEL_2, freq, resolution);
  ledcSetup(PWM_CHANNEL_3, freq, resolution);

  // Gán PWM cho các chân ENA/ENB
  ledcAttachPin(ENA1, PWM_CHANNEL_0);
  ledcAttachPin(ENB1, PWM_CHANNEL_1);
  ledcAttachPin(ENA2, PWM_CHANNEL_2);
  ledcAttachPin(ENB2, PWM_CHANNEL_3);

  // Stop when robot start up
  motorSpin(0, 0, 0, 0);
}

void moveForward(int speed) {  motorSpin(speed, speed, speed, speed);  }
void moveBackward(int speed) {  motorSpin(-speed, -speed, -speed, -speed);  }
void turnRight(int speed) {  motorSpin(speed, -speed, speed, -speed);  }
void turnLeft(int speed) {  motorSpin(-speed, speed, -speed, speed);  }
void rotateRight(int speed) { motorSpin(speed, -speed, speed, -speed); }
void rotateLeft(int speed) { motorSpin(-speed, speed, -speed, speed); }

void handleCommandMotor(char cmd){
    switch (cmd){
        case 'F' :
            moveForward(MOTOR_SPEED);  Serial.println(cmd);  break;
        case 'B' :
            moveBackward(MOTOR_SPEED);  Serial.println(cmd);  break;
        case 'R':
            turnRight(MOTOR_SPEED);   Serial.println(cmd);  break;
        case 'L':
            turnLeft(MOTOR_SPEED);  Serial.println(cmd);  break;
        case 'G':
            rotateRight(MOTOR_SPEED);  Serial.println(cmd);  break;
        case 'H':
            rotateLeft(MOTOR_SPEED);  Serial.println(cmd);  break;
        case 'S':
            motorSpin(0, 0, 0, 0);  Serial.println(cmd);  break;
        default :  break;
    }
}

