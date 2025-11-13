#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

//WiFi and MQTT config
const char* ssid = "QUANGHUY";
const char* password = "123456789";
const char* mqttServer = "172.19.233.47";
const char* clinetID = "espServo";
const int mqttPort = 1883;

extern WiFiClient espClient;
extern PubSubClient client;
                     