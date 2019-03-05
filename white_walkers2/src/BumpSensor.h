#ifndef BumpSensor_h
#define BumpSensor_h

#include <Arduino.h>
#include "Motor.h"
#include "Sensor.h"


class BumpSensor
{

public:
  BumpSensor();
  // desired direction is if the robot is moving "forward" or "backward" based on what's considered
  // such from the robot
  BumpSensor(int limit_pin);
  int checkSensor();
  int limit_pin;
	
private:
};

#endif