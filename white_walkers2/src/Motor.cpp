

#include <Arduino.h>
#include "Motor.h"

Motor::Motor(){
}


Motor::Motor(int enablePin, int dirPin, int straightDir){
	this->enablePin = enablePin;
  this->dirPin = dirPin;
  this->straightDir = straightDir;
	pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  this->setSpeed(0);
}


void Motor::setSpeed(int16_t speed){
	int desired_dir = 1;
  if (speed < 0) {
    desired_dir = -1;
  }
  int dir_out = desired_dir*straightDir;
  if (dir_out==1) {
    digitalWrite(this->dirPin, HIGH);
  }
  else{
    digitalWrite(this->dirPin, LOW);
  }
  int speed_out = abs(speed);
  analogWrite(this->enablePin, speed_out);
  this->speed = speed;
}

int16_t Motor::getSpeed() {
  return this->speed;
}