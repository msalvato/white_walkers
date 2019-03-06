#ifndef LineFollow_h
#define LineFollow_h

#include <Arduino.h>
#include "Motor.h"
#include "Sensor.h"


class LineFollow
{

public:
  LineFollow();
  // desired direction is if the robot is moving "forward" or "backward" based on what's considered
  // such from the robot
  LineFollow(Motor white_motor, Motor black_motor, Sensor white_sensor, Sensor black_sensor, uint16_t base_speed, int desired_dir);
  void initialize();
  void drive();
  Motor white_motor, black_motor;
  Sensor white_sensor, black_sensor;
  int32_t desired_dir;
  int32_t loop_time, integral, prior_error, white_adjust, black_adjust, base_speed;
  IntervalTimer timer;
  int32_t WHITE_VALUE, BLACK_VALUE;
	
private:
  float KI = 0;
  float KD = 0;
  float KP = .2;
};

#endif