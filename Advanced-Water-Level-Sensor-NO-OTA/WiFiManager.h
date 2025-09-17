#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>

class WiFiManager {
  private:
    const char* ssid;
    const char* password;
    const char* ap_ssid;
    const char* ap_password;
    unsigned long wifiTimeout;
    bool apMode;
    unsigned long startAttemptTime;

  public:
    WiFiManager(const char* ssid, const char* password, const char* ap_ssid, const char* ap_password, unsigned long wifiTimeout);
    void connectToWiFi();
    void enterAPMode();
    void handleAP();
    bool isConnected();
};

#endif
