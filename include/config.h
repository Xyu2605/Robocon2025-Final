#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

//WiFi and MQTT config
const char* ssid = "Phu cu to";
const char* password = "12345679";
const char* mqttServer = "192.168.137.173";
const char* clinetID = "espServo";
const int mqttPort = 1883;

extern WiFiClient espClient;
extern PubSubClient client;
                     