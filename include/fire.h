#pragma once

#define RPWM 18
#define LPWM 19
#define R_EN 2
#define L_EN 4

#define PWM_CHANNEL_R 0
#define PWM_CHANNEL_L 1
constexpr  int freq = 20000;  
constexpr  int resolution = 8;
extern int motorSpeed;
extern int motorSpeedLevel;

void initFire();
void on();
void off();
void changeMotorSpeedLevel(int delta);
void handleCommandMotor(char cmd);

