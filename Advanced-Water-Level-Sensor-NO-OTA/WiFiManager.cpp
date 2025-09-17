#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password, const char* ap_ssid, const char* ap_password, unsigned long wifiTimeout) {
  this->ssid = ssid;
  this->password = password;
  this->ap_ssid = ap_ssid;
  this->ap_password = ap_password;
  this->wifiTimeout = wifiTimeout;
  this->apMode = false;
  this->startAttemptTime = 0;
}

void WiFiManager::connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiTimeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }
}

void WiFiManager::enterAPMode() {
  WiFi.disconnect();
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("AP Mode Enabled. SSID: " + String(ap_ssid));
  apMode = true;
  startAttemptTime = millis();
}

void WiFiManager::handleAP() {
  if (apMode && millis() - startAttemptTime < 300000) { // AP for 5 minutes
    Serial.println("Scanning WiFi networks...");
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm)");
    }
    connectToWiFi();
  } else if (millis() - startAttemptTime >= 300000) {
    Serial.println("AP mode timeout, retrying WiFi connection...");
    apMode = false;
    WiFi.softAPdisconnect(true);
    connectToWiFi();
  }
}

bool WiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
