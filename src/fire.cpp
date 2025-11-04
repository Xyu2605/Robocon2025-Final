#include <Arduino.h>
#include "fire.h"

int motorSpeed = 200;
int motorSpeedLevel = 25;

void on() {

    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, LOW);
    ledcWrite(PWM_CHANNEL_R, motorSpeed);
    ledcWrite(PWM_CHANNEL_L, 0);
    Serial.printf("Motor ON, speed = %d\n", motorSpeed);
}

void off() {
    digitalWrite(R_EN, LOW);
    digitalWrite(L_EN, LOW);
    ledcWrite(PWM_CHANNEL_R, 0);
    ledcWrite(PWM_CHANNEL_L, 0);
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
    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);

    ledcSetup(PWM_CHANNEL_R, freq, resolution);
    ledcSetup(PWM_CHANNEL_L, freq, resolution);
    ledcAttachPin(RPWM, PWM_CHANNEL_R);
    ledcAttachPin(LPWM, PWM_CHANNEL_L);
    off();
}
