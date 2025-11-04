#pragma once

#define PWM_CHANNEL_R 0
#define PWM_CHANNEL_L 1
#define R_EN 11
#define L_EN 12

constexpr  int freq = 20000;  
constexpr  int resolution = 8;
extern int motorSpeed;
extern int motorSpeedLevel;

void initFire();
void on();
void off();
void changeMotorSpeedLevel(int delta);
void handleCommandMotor(char cmd);

