#include "BumpSensor.h"

BumpSensor::BumpSensor(){

};

BumpSensor::BumpSensor(int limit_pin){
    this->limit_pin = limit_pin;
    pinMode(limit_pin,INPUT);
};

int BumpSensor::checkSensor() {
    return digitalRead(limit_pin);
};