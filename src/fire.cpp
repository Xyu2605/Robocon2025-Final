#include <Arduino.h>
#include "fire.h"

int motorSpeed = 200;
int motorSpeedLevel = 25;

void on() {
    ledcWrite(PWM_CHANNEL_R, motorSpeed);
    ledcWrite(PWM_CHANNEL_L, 0);
    Serial.printf("Motor ON, speed = %d\n", motorSpeed);
}

void off() {
    ledcWrite(PWM_CHANNEL_R, 0);
    ledcWrite(PWM_CHANNEL_L, 0);
    Serial.println("Motor OFF");
}

void changeMotorSpeedLevel(int delta) {
    motorSpeed = constrain(motorSpeed + delta, 0, 255);
    ledcWrite(PWM_CHANNEL_R, motorSpeed); 

    if (delta > 0)
        Serial.printf("Tăng tốc độ: %d\n", motorSpeed);
    else
        Serial.printf("Giảm tốc độ: %d\n", motorSpeed);
}

void handleCommandMotor(char cmd) {
    switch (cmd) {
        case 'U': on(); break;
        case 'Y': off(); break;
        case '1': changeMotorSpeedLevel(motorSpeedLevel); break;
        case '0': changeMotorSpeedLevel(-motorSpeedLevel); break;
    }
}

void initFire() {
    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);
    ledcSetup(PWM_CHANNEL_R, freq, resolution);
    ledcSetup(PWM_CHANNEL_L, freq, resolution);
    ledcAttachPin(R_EN, PWM_CHANNEL_R);
    ledcAttachPin(L_EN, PWM_CHANNEL_L);
    off();
}
