#pragma once
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define SDA_PIN 18
#define SCL_PIN 19
#define SERVO_MIN 150
#define SERVO_MAX 600
#define SERVO_FREQ 50
#define SERVO_1 0
#define SERVO_2 1
#define SERVO_3 2

const int stepAngle = 5;
const int servoMoveSpeed = 20;
extern int angle1;
extern int angle2;
extern int angle3;
extern int defaultAngles[];
extern int takeTheBallAngles[];
extern int dropTheBallAngles[];

void initServo();
void setDefaultArm();
void servoUp(int id);
void servoDown(int id);
void handleCommandServo(char cmd);
void takeTheBall();
void dropTheBall();
void updateArm(int id, int target);
void autoUpdateArm(int targetAngles[], int numServos);