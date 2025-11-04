#pragma once

#define MAGNET_PIN 32   

void initMagnet();
void magnetOn();
void magnetOff();
void handleCommandMagnet(char cmd);
