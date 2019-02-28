#ifndef Motor_h
#define Motor_h

#include <Arduino.h>


class Motor
{

public:
  Motor();
  Motor(int enablePin, int dirPin, int straightDir);
  void setSpeed(int16_t speed);
  int16_t getSpeed();
	
private:
  int16_t speed, enablePin, dirPin, straightDir;
};

#endif