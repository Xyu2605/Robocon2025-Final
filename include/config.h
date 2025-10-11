#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT config
const char* ssid = "thuchanhAT T5";
const char* password = "12345679";
const char* mqttServer = "172.19.43.72";
const int mqttPort = 1883;

extern WiFiClient espClient;
extern PubSubClient client;
