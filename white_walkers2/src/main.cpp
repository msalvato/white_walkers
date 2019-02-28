#include <Arduino.h>
#include "Motor.h"
#include "LineFollow.h"
int dirPinLeft = 5;
int enablePinLeft = 4;
int dirPinRight = 2;
int enablePinRight = 3;

int sensorPinIn = 19;
Motor left_motor;
Motor right_motor;
LineFollow to_armory;
LineFollow to_kings;

uint16_t BLACK_VALUE = 0;
uint16_t WHITE_VALUE = 0;
uint16_t KI = 0;
uint16_t KD = 0;
float KP = .2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("hello");
  left_motor = Motor(enablePinLeft, dirPinLeft, -1);
  right_motor = Motor(enablePinRight, dirPinRight, 1);
}

void loop() {
// put your main code here, to run repeatedly:
left_motor.setSpeed(150);
right_motor.setSpeed(150);
}


// for some reason interval timer won't use a class function so we're doing this annoying thing
void drivetoArmory() {
    uint16_t white_error = -(to_armory.white_sensor.getValue() - WHITE_VALUE);
    uint16_t black_error = to_armory.black_sensor.getValue() - BLACK_VALUE;
    // if white error is bigger, we're moving black, slow down white motor
    uint16_t overall_error = white_error - black_error;
    to_armory.integral += KI*overall_error*to_armory.loop_time;
    uint16_t derivative = (KD*(overall_error - to_armory.prior_error))/to_armory.loop_time;
    uint16_t control_out = to_armory.integral + derivative + KP*overall_error;
    to_armory.prior_error = overall_error;
    to_armory.white_adjust -= control_out;
    to_armory.black_adjust += control_out;
    constrain(to_armory.white_adjust, -100, 100);
    constrain(to_armory.black_adjust,-100,100);
    to_armory.white_motor.setSpeed(to_armory.base_speed + to_armory.white_adjust);
    to_armory.black_motor.setSpeed(to_armory.base_speed + to_armory.black_adjust);
}