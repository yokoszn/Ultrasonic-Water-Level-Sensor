#ifndef WEBPAGEMANAGER_H
#define WEBPAGEMANAGER_H

#include <WiFi.h>
#include <WebServer.h>
#include "UltrasonicSensor.h"

class WebPageManager {
  private:
    WebServer server;
    UltrasonicSensor& sensor;

  public:
    WebPageManager(UltrasonicSensor& sensor);
    void setupServer();
    void handleClient();
};

#endif
