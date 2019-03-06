#include <Arduino.h>
#include "AlignLauncher.h"

AlignLauncher::AlignLauncher() {

}
AlignLauncher::AlignLauncher(Motor front_motor, Motor back_motor, Sensor left_sensor, Sensor right_sensor, int desired_dir, int32_t error_threshold){
    this->front_motor = front_motor;
    this->back_motor = back_motor;
    this->left_sensor = left_sensor;
    this->right_sensor = right_sensor;
    this->desired_dir = desired_dir;
    this->base_speed = base_speed;
    this->timer = timer;
    this->error_threshold = error_threshold; 
    this->initialize();
}
void AlignLauncher::activate(uint32_t loop_time) {
    this->loop_time = loop_time;
    this->integral = 0;
    this->prior_error = 0;
    white_adjust = 0;
    black_adjust = 0;
}

// for some reason interval timer won't use a class function so we're doing this annoying thing
void AlignLauncher::align() {
    int32_t left_val = this->left_sensor.getValue() - this->LEFT_VALUE;
    int32_t right_val = this->right_sensor.getValue() - this->RIGHT_VALUE;
    // if white error is bigger, we're moving black, slow down white motor
    int32_t overall_error = left_val - right_val;
    //this->integral += KI*overall_error*this->loop_time;
    //int32_t derivative = (KD*(overall_error - this->prior_error))/this->loop_time;
    // this->integral + derivative + 
    this->control_out = KP*overall_error;
    //this->prior_error = overall_error;
    control_out = constrain(control_out,-50,50);
    this->front_motor.setSpeed(-control_out);
    this->back_motor.setSpeed(control_out);   
}

int AlignLauncher::alignmentDir(){
    int32_t left_val = this->left_sensor.getValue() - this->LEFT_VALUE;
    int32_t right_val = this->right_sensor.getValue() - this->RIGHT_VALUE;
    int32_t overall_error = left_val - right_val;
    if (overall_error < -this->error_threshold) {
        return -1;
    }
    else if (overall_error > this->error_threshold)
    {
        return 1;
    }
    
    return 0;
}

void AlignLauncher::initialize() {
    int num_samples = 10;
    this->LEFT_VALUE = 0;
    this->RIGHT_VALUE = 0;
    for (int i = 0; i < 10; i++) {
        this->LEFT_VALUE += this->left_sensor.getValue();
        this->RIGHT_VALUE += this->right_sensor.getValue();
    }
    this->LEFT_VALUE /= num_samples;
    this->RIGHT_VALUE /= num_samples;
}

int AlignLauncher::alignWithCross(LineFollow forward_line, LineFollow backward_line) {
    if (this->alignmentDir() != 0) {
        if (this->alignmentDir() == 1) {
            forward_line.drive();
            return 0;
        }
        if (this->alignmentDir() == -1) {
            backward_line.drive();
            return 0;
        }
    }
    else{
        return 1;
    }
    return 0;
}

int AlignLauncher::checkCrossedCross() {
    if (this->left_sensor.getValue() < this->LEFT_VALUE - 300) {
        crossed_cross = 1;
    }
    return crossed_cross;
}