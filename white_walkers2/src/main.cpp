#include <Arduino.h>
#include "Motor.h"
int dirPinLeft = 5;
int enablePinLeft = 4;
int dirPinRight = 2;
int enablePinRight = 3;

int sensorPinIn = 19;
Motor left_motor;
Motor right_motor;

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