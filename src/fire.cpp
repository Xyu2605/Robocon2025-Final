#include <Arduino.h>
#include "fire.h"

int motorSpeed = 200;
int motorSpeedLevel = 25;
bool fireOn = false;

void on() {
    fireOn = true;
    ledcWrite(PWM_CHANNEL_R, motorSpeed);
    ledcWrite(PWM_CHANNEL_L, 0);  
    Serial.printf("Motor ON, speed = %d\n", motorSpeed);
}

void off() {
    fireOn = false;
    ledcWrite(PWM_CHANNEL_R, 0);
    ledcWrite(PWM_CHANNEL_L, 0);
}

void changeMotorSpeedLevel(int delta) {
    motorSpeed = constrain(motorSpeed + delta, 0, 255);
    if(fireOn){
        ledcWrite(PWM_CHANNEL_R, motorSpeed);
        ledcWrite(PWM_CHANNEL_L, 0);
    }
    
    if (delta > 0)
        Serial.printf("Tăng tốc độ: %d\n", motorSpeed);
    else
        Serial.printf("Giảm tốc độ: %d\n", motorSpeed);
}


void motor2On() {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_1, speed);
    Serial.printf("Motor nạp bóng: ON , speed = %d\n", speed);
}

void motor2Off() {
    
    ledcWrite(PWM_CHANNEL_1, 0);
    Serial.println("Motor nạp bóng: Off");
}

void handleCommandMotor(char cmd) {
    switch (cmd) {
        case 'U': on(); break;
        case 'Y': off(); break;
        case '2': motor2On(); break;
        case '3': motor2Off(); break;
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
    
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcSetup(PWM_CHANNEL_1, freq2, resolution);
    ledcAttachPin(ENA1, PWM_CHANNEL_1);

    off();  
    motor2Off();
    Serial.println("[Fire] initialized!");
}
