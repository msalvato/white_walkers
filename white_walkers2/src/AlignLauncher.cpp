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

int AlignLauncher::checkCrossedCross() {
    if (this->left_sensor.getValue() < this->LEFT_VALUE - 500) {
        crossed_cross = 1;
    }
    return crossed_cross;
}