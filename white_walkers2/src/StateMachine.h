#ifndef StateMachine_h
#define StateMachine_h

#include <Arduino.h>
#include <Metro.h>
#include "Motor.h"
#include "Sensor.h"
#include "LineFollow.h"
#include "AlignLauncher.h"
#include "BumpSensor.h"
#include "Motor.h"

enum State {
    toarmory,
    hitbump,
    loadballs,
    tokings,
    aligningkings,
    launching
};

class StateMachine
{

public:
  StateMachine();
  StateMachine(LineFollow to_armory, LineFollow to_kings, AlignLauncher align_kings, BumpSensor bump_sensor, Motor left_motor, Motor right_motor);
  void machineLoop();
  void setStart(State start_state);
  State current_state = toarmory;
  // desired direction is if the robot is moving "forward" or "backward" based on what's considered
  // such from the robot
	
private:
  LineFollow to_armory, to_kings;
  AlignLauncher align_kings;
  BumpSensor bump_sensor;
  Motor left_motor, right_motor;
  Metro lever_timer = Metro(3000);
  Metro load_timer = Metro(5000);
  Metro ignore_blue_tape = Metro(5000);
  
};

#endif