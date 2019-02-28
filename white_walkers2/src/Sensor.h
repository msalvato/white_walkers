#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>


class Sensor
{

public:
  Sensor();
  Sensor(int sensorPin);
  int getValue();
	
private:
  int sensorPin;
};

#endif