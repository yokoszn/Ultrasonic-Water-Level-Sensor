#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor {
  private:
    int trigPin;
    int echoPin;
    float maxTankHeight;
    float tankCapacity;  // in liters

  public:
    UltrasonicSensor(int trigPin, int echoPin, float maxTankHeight, float tankCapacity);

    float getDistance();
    float getWaterLevelPercentage();
    float getWaterLevelInLiters();

    // Getter methods for private variables
    int getTrigPin();        
    int getEchoPin();        
    float getMaxTankHeight(); 
    float getTankCapacity();  
};

#endif
