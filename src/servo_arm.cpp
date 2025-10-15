#include "servo_arm.h"
#include <Arduino.h>

int angle1 = 0;
int angle2 = 110;
int angle3 = 145;
int stepAngle = 5;

Servo servo1;
Servo servo2;
Servo servo3;

void updateArm(int id, int target) {
    int *anglePtr = nullptr;
    Servo *servoPtr = nullptr;

    switch (id) {
        case 1: anglePtr = &angle1; servoPtr = &servo1; break;
        case 2: anglePtr = &angle2; servoPtr = &servo2; break;
        case 3: anglePtr = &angle3; servoPtr = &servo3; break;
        default: return;
    }

    target = constrain(target, 0, 180);
    *anglePtr = target;
    servoPtr->write(*anglePtr);
}

void autoUpdateArm(int id, int target) {
    int *anglePtr = nullptr;
    Servo *servoPtr = nullptr;

    switch (id) {
        case 1: anglePtr = &angle1; servoPtr = &servo1; break;
        case 2: anglePtr = &angle2; servoPtr = &servo2; break;
        case 3: anglePtr = &angle3; servoPtr = &servo3; break;
        default: return;
    }

    target = constrain(target, 0, 180);
    unsigned long startTime = millis();

    while (*anglePtr != target && millis() - startTime < 5000) { // tránh treo
        if (*anglePtr < target) (*anglePtr)++;
        else if (*anglePtr > target) (*anglePtr)--;

        servoPtr->write(*anglePtr);
        delay(15);
    }
}

void takeTheBall() {
    autoUpdateArm(3, 80);
    delay(200);
    autoUpdateArm(2, 85);
    delay(200);
    autoUpdateArm(3, 125);
    delay(200);
}

void throwTheBall() {
    autoUpdateArm(2, 145);
    delay(200);
    autoUpdateArm(1, 180);
    delay(200);
    autoUpdateArm(3, 180);
    delay(200);
}

void setDefaultArm() {
    autoUpdateArm(1, angle1);
    delay(300);
    autoUpdateArm(2, angle2);
    delay(300);
    autoUpdateArm(3, angle3);
    delay(300);
}

void servoUp(int id) {
    switch (id) {
        case 1: updateArm(1, angle1 + stepAngle); break;
        case 2: updateArm(2, angle2 + stepAngle); break;
        case 3: updateArm(3, angle3 + stepAngle); break;
    }
    Serial.println("S1=" + String(angle1) + " | S2=" + String(angle2) + " | S3=" + String(angle3));
}

void servoDown(int id) {
    switch (id) {
        case 1: updateArm(1, angle1 - stepAngle); break;
        case 2: updateArm(2, angle2 - stepAngle); break;
        case 3: updateArm(3, angle3 - stepAngle); break;
    }
    Serial.println("S1=" + String(angle1) + " | S2=" + String(angle2) + " | S3=" + String(angle3));
}

void handleCommandServo(char cmd) {
    switch (cmd) {
        case 'Q': servoUp(1); break;
        case 'A': servoDown(1); break;
        case 'W': servoUp(2); break;
        case 'X': servoDown(2); break;
        case 'E': servoUp(3); break;
        case 'D': servoDown(3); break;
        case 'Z': takeTheBall(); break;
        case 'N': throwTheBall(); break;
        default: break;
    }
}

void initServo() {
    servo1.attach(14, 500, 2500);
    servo2.attach(13, 500, 2500);
    servo3.attach(12, 500, 2500);
    setDefaultArm();
}
