#pragma once

// Động cơ bắn bóng
#define RPWM 18
#define LPWM 19
#define R_EN 2
#define L_EN 4

#define PWM_CHANNEL_R 0
#define PWM_CHANNEL_L 1
constexpr  int freq = 20000;  
extern int motorSpeed;
extern int motorSpeedLevel;

// Động cơ nạp bóng
#define PWM_CHANNEL_1 2
#define ENA1 13
#define IN1 12
#define IN2 14
const int speed = 150; 

constexpr  int resolution = 8;

void initFire();
void on();
void off();
void changeMotorSpeedLevel(int delta);
void handleCommandMotor(char cmd);

