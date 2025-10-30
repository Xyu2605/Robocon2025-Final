#include <Arduino.h>
#include "magnet.h"

bool magnetState = false;

void initMagnet() {
  pinMode(MAGNET_PIN, OUTPUT);
  digitalWrite(MAGNET_PIN, LOW);  // Tắt nam châm lúc khởi động
  magnetState = false;
  Serial.println("Magnet initialized");
}

void magnetOn() {
  digitalWrite(MAGNET_PIN, HIGH);
  magnetState = true;
  Serial.println("MAGNET ON");
}

void magnetOff() {
  digitalWrite(MAGNET_PIN, LOW);
  magnetState = false;
  Serial.println("MAGNET OFF");
}


void handleCommandMagnet(char cmd) {
  switch (cmd) {
    case 'B':  
      magnetOn();
      break;
    case 'T':  
      magnetOff();
      break;
    default:
      break;
  }
}
