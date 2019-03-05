#include <Arduino.h>
#include "Motor.h"
#include "LineFollow.h"
#include "Sensor.h"
#include "AlignLauncher.h"
#include "StateMachine.h"

int dirPinLeft = 5;
int enablePinLeft = 4;
int dirPinRight = 2;
int enablePinRight = 3;

Motor left_motor;
Motor right_motor;
Sensor fw_sensor = Sensor(17);
Sensor fb_sensor = Sensor(16);
Sensor bb_sensor = Sensor(18);
Sensor bw_sensor = Sensor(19);
Sensor l_align_sensor = Sensor(14);
Sensor r_align_sensor = Sensor(15);
BumpSensor bump_sensor = BumpSensor(20);


LineFollow to_armory;
LineFollow to_kings;
AlignLauncher align_kings;
StateMachine state_machine;


float KI = 0;
float KD = 0;
float KP = .2;
IntervalTimer armory_timer;

void driveToArmory();
int limitpin = 20;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("hello");
  left_motor = Motor(enablePinLeft, dirPinLeft, -1);
  right_motor = Motor(enablePinRight, dirPinRight, 1);
  left_motor.setSpeed(0);
  right_motor.setSpeed(0);
  delay(5000);
  Serial.println("too late");
  to_armory = LineFollow(left_motor, right_motor, fw_sensor, fb_sensor, 150, 1);
  to_kings = LineFollow(left_motor, right_motor, bw_sensor, bb_sensor, 150, -1);
  align_kings = AlignLauncher(right_motor, left_motor, l_align_sensor, r_align_sensor, 1, 10);
  state_machine = StateMachine(to_armory, to_kings, align_kings, bump_sensor, left_motor, right_motor);
}

void loop() {
// put your main code here, to run repeatedly:
state_machine.machineLoop();
}


// // for some reason interval timer won't use a class function so we're doing this annoying thing
// void driveToArmory() {
//     int32_t white_error = -(to_armory.white_sensor.getValue() - WHITE_VALUE);
//     int32_t black_error = to_armory.black_sensor.getValue() - BLACK_VALUE;
//     // if white error is bigger, we're moving black, slow down white motor
//     int32_t overall_error = white_error - black_error;
//     //to_armory.integral += KI*overall_error*to_armory.loop_time;
//     //int32_t derivative = (KD*(overall_error - to_armory.prior_error))/to_armory.loop_time;
//     // to_armory.integral + derivative + 
//     int32_t control_out = KP*overall_error;
//     to_armory.prior_error = overall_error;
//     to_armory.white_adjust = -control_out;
//     to_armory.black_adjust = control_out;
//     to_armory.white_adjust = constrain(to_armory.white_adjust, -100, 100);
//     to_armory.black_adjust = constrain(to_armory.black_adjust,-100,100);
//     to_armory.white_motor.setSpeed(to_armory.base_speed + to_armory.white_adjust);
//     to_armory.black_motor.setSpeed(to_armory.base_speed + to_armory.black_adjust);
    
// }