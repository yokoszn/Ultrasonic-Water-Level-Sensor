#include <WiFiManager.h>
#include <MQTTManager.h>
#include <UltrasonicSensor.h>
#include <WebPageManager.h>

WiFiClient espClient;

// WiFi details
const char* ssid = "Terrace_EXT";
const char* password = "xxxxxxxx";
const char* ap_ssid = "ESP32_C3_AP";
const char* ap_password = "12345678";

// MQTT details
const char* mqtt_server = "192.168.0.163";
const int mqtt_port = 1885;
const char* mqtt_user = "mqtt-user";
const char* mqtt_password = "techposts";

// Tank and Sensor details
const float tank_height = 130.0; // Height of the tank in cm
const float tank_capacity = 2000.0; // Tank capacity in liters

// Sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Instances of our custom classes
WiFiManager wifiManager(ssid, password, ap_ssid, ap_password, 120000);  // 120 seconds for WiFi timeout
MQTTManager mqttManager(espClient, mqtt_server, mqtt_port, mqtt_user, mqtt_password);
UltrasonicSensor ultrasonicSensor(trigPin, echoPin, tank_height, tank_capacity);
WebPageManager webPageManager(ultrasonicSensor);

void setup() {
  Serial.begin(115200);

  // Try to connect to WiFi
  wifiManager.connectToWiFi();

  // If not connected, start AP mode
  if (!wifiManager.isConnected()) {
    wifiManager.enterAPMode();
  }

  // Setup web server
  webPageManager.setupServer();
}

void loop() {
  // Handle WiFi connection and AP logic
  if (!wifiManager.isConnected()) {
    wifiManager.handleAP();
  } else {
    // Handle MQTT connection and sensor data publishing
    if (!mqttManager.isConnected()) {
      mqttManager.connectMQTT();
    }
    mqttManager.loop();

    // Measure water level
    float waterLevelPercentage = ultrasonicSensor.getWaterLevelPercentage();
    float waterLevelInLiters = ultrasonicSensor.getWaterLevelInLiters();

    // Send data to MQTT
    char msg[50];
    sprintf(msg, "Water Level: %.2f%%, %.2f liters", waterLevelPercentage, waterLevelInLiters);
    mqttManager.publishMessage("water-level/sensor", msg);

    Serial.println(msg);

    // Handle web server for showing tank status and adjusting tank height
    webPageManager.handleClient();

    delay(5000); // Delay between readings (5 seconds)
  }
}
