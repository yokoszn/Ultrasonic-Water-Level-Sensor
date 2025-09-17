#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin, float maxTankHeight, float tankCapacity) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  this->maxTankHeight = maxTankHeight;
  this->tankCapacity = tankCapacity;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float UltrasonicSensor::getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.034) / 2;
  return distance;
}

float UltrasonicSensor::getWaterLevelPercentage() {
  float distance = getDistance();
  if (distance > maxTankHeight) distance = maxTankHeight; // Cap the distance
  
  float waterHeight = maxTankHeight - distance;
  float percentage = (waterHeight / maxTankHeight) * 100;
  return percentage;
}

float UltrasonicSensor::getWaterLevelInLiters() {
  float percentage = getWaterLevelPercentage();
  float liters = (percentage / 100) * tankCapacity;
  return liters;
}

// Getter methods
int UltrasonicSensor::getTrigPin() {
  return trigPin;
}

int UltrasonicSensor::getEchoPin() {
  return echoPin;
}

float UltrasonicSensor::getMaxTankHeight() {
  return maxTankHeight;
}

float UltrasonicSensor::getTankCapacity() {
  return tankCapacity;
}
