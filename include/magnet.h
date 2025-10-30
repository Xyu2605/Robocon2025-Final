#pragma once

#define MAGNET_PIN 5 

void initMagnet();
void magnetOn();
void magnetOff();
void handleCommandMagnet(char cmd);
