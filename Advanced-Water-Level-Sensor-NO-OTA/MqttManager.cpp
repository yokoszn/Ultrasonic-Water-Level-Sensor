#include "MQTTManager.h"

MQTTManager::MQTTManager(WiFiClient& espClient, const char* server, int port, const char* user, const char* password) : client(espClient) {
  this->mqtt_server = server;
  this->mqtt_port = port;
  this->mqtt_user = user;
  this->mqtt_password = password;
  client.setServer(mqtt_server, mqtt_port);
}

void MQTTManager::connectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32C3Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void MQTTManager::publishMessage(const char* topic, const char* message) {
  client.publish(topic, message);
}

bool MQTTManager::isConnected() {
  return client.connected();
}

void MQTTManager::loop() {
  client.loop();
}
