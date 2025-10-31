#include <Arduino.h>
#include "fire.h"

int motorSpeed = 200;
int motorSpeedLevel = 25;

void on(){

    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);
    ledcWrite(pwmChannelR, motorSpeed);
    ledcWrite(pwmChannelL, motorSpeed);
    Serial.printf("Motor ON, speed = %d\n", motorSpeed);
}

void off(){

    digitalWrite(R_EN, LOW);
    digitalWrite(L_EN, LOW);
    ledcWrite(pwmChannelR, 0);
    ledcWrite(pwmChannelL, 0);
    Serial.println("Motor OFF");
}

void changeMotorSpeedLevel(int delta) {
    motorSpeed = constrain(motorSpeed + delta, 0, 255); 
    ledcWrite(pwmChannelR, motorSpeed);
    ledcWrite(pwmChannelL, motorSpeed);

    if (delta > 0)
        Serial.printf("Tăng tốc độ: %d\n", motorSpeed);
    else
        Serial.printf("Giảm tốc độ: %d\n", motorSpeed);
}

void handleCommandMotor(char cmd){
    switch(cmd){
        case 'U': on(); break;
        case 'Y': off(); break;
        case '1': changeMotorSpeedLevel(motorSpeedLevel); break;
        case '0': changeMotorSpeedLevel(-motorSpeedLevel); break;
    }
}

void initFire(){

    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);

    ledcSetup(pwmChannelR, freq, resolution);
    ledcSetup(pwmChannelL, freq, resolution);
    ledcAttachPin(RPWM, pwmChannelR);
    ledcAttachPin(LPWM, pwmChannelL);

    off();
}