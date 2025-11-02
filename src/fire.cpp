#include <Arduino.h>
#include "fire.h"

int motorSpeed = 200;
int motorSpeedLevel = 25;

void on() {
    ledcWrite(PWM_CHANNEL, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    Serial.printf("Motor ON, speed = %d\n", motorSpeed);
}

void off() {
    ledcWrite(PWM_CHANNEL, 0); // Dừng PWM hoàn toàn
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    Serial.println("Motor OFF");
}

void changeMotorSpeedLevel(int delta) {
    motorSpeed = constrain(motorSpeed + delta, 0, 255);
    ledcWrite(PWM_CHANNEL, motorSpeed); 

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
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    ledcSetup(PWM_CHANNEL, freq, resolution);
    ledcAttachPin(ENA, PWM_CHANNEL);
    off();
}
