#include <Arduino.h>
#include "servo_arm.h"
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void mqttCallback(char* topic, byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)message[i];
  }
  Serial.print("MQTT ["); Serial.print(topic); Serial.print("]: "); Serial.println(msg);

  if (String(topic) == "servo/cmd") {
    if (msg.length() > 0) {
      handleCommandServo(msg[0]);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT Server ...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected!");
      client.subscribe("robot/cmd");
    } else {
      Serial.print("Error: ");
      Serial.print(client.state());
      Serial.println("Try to connect to MQTT after 5s.");
      delay(5000);
    }
  }
}

void setup(){
  Serial.begin(115200); 
  //WiFi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  Serial.print("\nWiFi connected. IP: ");
  Serial.println(WiFi.localIP());
  // MQTT setup
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);
  //Initializating robot
  initServo();
  Serial.println("Robot is ready");
}

void loop(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Lost connecting WiFi, try again...");
    WiFi.reconnect();
    delay(5000);
  }
  
  if(!client.connected()){
    reconnect();
  }
  client.loop();
}