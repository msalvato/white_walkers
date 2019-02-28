#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor(){

}

Sensor::Sensor(int sensorPin){
    pinMode(sensorPin, INPUT);
    this->sensorPin = sensorPin;
}


int Sensor::getValue(){
    return analogRead(this->sensorPin);
}
