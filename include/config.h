#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

//WiFi and MQTT config
const char* ssid = "Kepler";
const char* password = "3141527182";
const char* mqttServer = "192.168.1.6";
const int mqttPort = 1883;

extern WiFiClient espClient;
extern PubSubClient client;
