#pragma once

#define RPWM 9     // PWM phải
#define LPWM 10    // PWM trái
#define R_EN 11    // Cho phép phải
#define L_EN 12    // Cho phép trái

// Cấu hình PWM
constexpr  int freq = 20000;   // Tần số PWM (Hz)
constexpr  int pwmChannelR = 0;
constexpr  int pwmChannelL = 1;
constexpr  int resolution = 8;
extern int motorSpeed;
extern int motorSpeedLevel;

void initFire();
void on();
void off();
void changeMotorSpeedLevel(int speed);
void handleCommandMotor(char cmd);

