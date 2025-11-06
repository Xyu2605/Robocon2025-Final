#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT config
const char* ssid = "minh";
const char* password = "alo12345";
const char* mqttServer = "192.168.70.225";
const int mqttPort = 1883;

extern WiFiClient espClient;
extern PubSubClient client;
