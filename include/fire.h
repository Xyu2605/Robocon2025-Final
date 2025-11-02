#pragma once

#define PWM_CHANNEL 0  
#define ENA 25    
#define IN1 26
#define IN2 27

constexpr  int freq = 20000;  
constexpr  int resolution = 8;
extern int motorSpeed;
extern int motorSpeedLevel;

void initFire();
void on();
void off();
void changeMotorSpeedLevel(int delta);
void handleCommandMotor(char cmd);

