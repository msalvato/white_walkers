#include <Arduino.h>
#include "Motor.h"
#include "LineFollow.h"
#include "Sensor.h"
#include "AlignLauncher.h"
#include "StateMachine.h"

int dirPinRight = 5;
int enablePinRight = 4;
int dirPinLeft = 2;
int enablePinLeft = 3;

Motor meghan; //left_motor;
Motor kate; //right_motor;
Sensor fw_sensor = Sensor(17);
Sensor fb_sensor = Sensor(16);
Sensor bb_sensor = Sensor(18);
Sensor bw_sensor = Sensor(19);
Sensor l_align_sensor = Sensor(14);
Sensor r_align_sensor = Sensor(15);
BumpSensor bump_sensor = BumpSensor(23);
OurServo william = OurServo(7, 20, 160); // flicker
OurServo harry = OurServo(8,5,55); // gate


LineFollow to_armory;
LineFollow to_kings;
AlignLauncher align_kings;
StateMachine state_machine;


float KI = 0;
float KD = 0;
float KP = .2;
IntervalTimer armory_timer;

void driveToArmory();
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //while(!Serial);
  //Serial.println("hello");
  meghan = Motor(enablePinLeft, dirPinLeft, -1);
  kate = Motor(enablePinRight, dirPinRight, 1);
  meghan.setSpeed(0);
  kate.setSpeed(0);
  delay(2000);
  //Serial.println("too late");
  to_armory = LineFollow(meghan, kate, fw_sensor, fb_sensor, 255, 1);
  to_kings = LineFollow(meghan, kate, bw_sensor, bb_sensor, 255, -1);
  align_kings = AlignLauncher(kate, meghan, l_align_sensor, r_align_sensor, 1, 10);
  state_machine = StateMachine(to_armory, to_kings, align_kings, bump_sensor, meghan, kate, william, harry);
  //state_machine.setStart(launching);
}

void loop() {
// put your main code here, to run repeatedly:
state_machine.machineLoop();
}