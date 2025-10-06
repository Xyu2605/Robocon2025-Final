#pragma once
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define SERVO_MIN 150
#define SERVO_MAX 600
#define SERVO_FREQ 50
#define SERVO_1 0
#define SERVO_2 1
#define SERVO_3 2

extern int angle1;
extern int angle2;
extern int angle3;
extern int stepAngle;
extern int servoMoveSpeed;
extern int defaultAngles[];
extern int grabAngles[];
extern int releaseAngles[];

void initServo();
void setDefaultArm();
void updateArm(int a, int id);
void servoUp(int id);
void servoDown(int id);
void handleCommandServo(char cmd);
void takeTheBall();
void throwTheBall();
void moveToTargetAngle(int id, int target);
void autoUpdateArm(int targetAngles[], int numServos);