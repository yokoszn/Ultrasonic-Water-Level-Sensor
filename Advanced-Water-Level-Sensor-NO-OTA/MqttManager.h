#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTManager {
  private:
    PubSubClient client;
    const char* mqtt_server;
    int mqtt_port;
    const char* mqtt_user;
    const char* mqtt_password;

  public:
    MQTTManager(WiFiClient& espClient, const char* server, int port, const char* user, const char* password);
    void connectMQTT();
    void publishMessage(const char* topic, const char* message);
    bool isConnected();
    void loop();
};

#endif
