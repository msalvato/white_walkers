#include <Arduino.h>
#include "LineFollow.h"

LineFollow::LineFollow() {

}
LineFollow::LineFollow(Motor white_motor, Motor black_motor, Sensor white_sensor, Sensor black_sensor, uint16_t base_speed, int desired_dir){
    this->white_motor = white_motor;
    this->black_motor = black_motor;
    this->white_sensor = white_sensor;
    this->black_sensor = black_sensor;
    this->desired_dir = desired_dir;
    this->base_speed = base_speed;
    this->timer = timer;
    this->initialize();
}

// for some reason interval timer won't use a class function so we're doing this annoying thing
void LineFollow::drive() {
    int32_t white_error = -(this->white_sensor.getValue() - WHITE_VALUE);
    int32_t black_error = this->black_sensor.getValue() - BLACK_VALUE;
    // if white error is bigger, we're moving black, slow down white motor
    int32_t overall_error = white_error - black_error;
    //this->integral += KI*overall_error*this->loop_time;
    //int32_t derivative = (KD*(overall_error - this->prior_error))/this->loop_time;
    // this->integral + derivative + 
    int32_t control_out = KP*overall_error;
    this->prior_error = overall_error;
    this->white_adjust = -control_out;
    this->black_adjust = control_out;
    this->white_adjust = constrain(this->white_adjust, -55, 55);
    this->black_adjust = constrain(this->black_adjust,-55,55);
    this->white_motor.setSpeed(this->desired_dir*(this->base_speed + this->white_adjust));
    this->black_motor.setSpeed(this->desired_dir*(this->base_speed + this->black_adjust));
    
}

void LineFollow::initialize() {
    int num_samples = 10;
    this->WHITE_VALUE = 0;
    this->BLACK_VALUE = 0;
    for (int i = 0; i < 10; i++) {
        this->WHITE_VALUE += this->white_sensor.getValue();
        this->BLACK_VALUE += this->black_sensor.getValue();
    }
    this->WHITE_VALUE /= num_samples;
    this->BLACK_VALUE /= num_samples;
}