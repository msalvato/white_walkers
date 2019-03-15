#ifndef AlignLauncher_h
#define AlignLauncher_h

#include <Arduino.h>
#include "Motor.h"
#include "Sensor.h"
#include "LineFollow.h"


class AlignLauncher
{

public:
  AlignLauncher();
  // desired direction is if the robot is moving "forward" or "backward" based on what's considered
  // such from the robot
  AlignLauncher(Motor front_motor, Motor back_motor, Sensor left_sensor, Sensor right_sensor, int desired_dir, int32_t error_threshold);
  void initialize();
  int checkCrossedCross();
  Motor front_motor, back_motor;
  Sensor left_sensor, right_sensor;
  int32_t desired_dir;
  int32_t control_out;
  int32_t loop_time, integral, prior_error, white_adjust, black_adjust, base_speed;
  int32_t LEFT_VALUE, RIGHT_VALUE;
  int32_t error_threshold;
  int crossed_cross = 0;
  IntervalTimer timer;
	
private:
  float KI = 0;
  float KD = 0;
  float KP = .5;
  int aligned_count = 0;
  
};

#endif