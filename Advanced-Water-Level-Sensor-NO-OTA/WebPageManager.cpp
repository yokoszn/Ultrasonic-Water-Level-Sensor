#include "WebPageManager.h"

WebPageManager::WebPageManager(UltrasonicSensor& sensor) : server(80), sensor(sensor) {}

void WebPageManager::setupServer() {
  server.on("/", [this]() {
    float percentage = sensor.getWaterLevelPercentage();
    float liters = sensor.getWaterLevelInLiters();
    
    String html = "<html><body>";
    html += "<h1>Tank Water Level</h1>";
    html += "<p>Water Level: " + String(percentage) + "%</p>";
    html += "<p>Water Volume: " + String(liters) + " liters</p>";
    html += "<form action='/update_height'>";
    html += "Tank Height: <input type='number' name='height' step='0.1'><input type='submit' value='Update'>";
    html += "</form>";
    html += "</body></html>";
    
    server.send(200, "text/html", html);
  });

  server.on("/update_height", [this]() {
    if (server.hasArg("height")) {
      float newHeight = server.arg("height").toFloat();
      sensor = UltrasonicSensor(sensor.getTrigPin(), sensor.getEchoPin(), newHeight, sensor.getTankCapacity()); // Use getter methods to access private variables
      server.send(200, "text/html", "Tank height updated to " + String(newHeight) + " cm");
    }
  });

  server.begin();
  Serial.println("Web server started!");
}

void WebPageManager::handleClient() {
  server.handleClient();
}
