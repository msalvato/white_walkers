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
    IntervalTimer timer;
    this->timer = timer;
}
void LineFollow::activate(uint32_t loop_time) {
    this->loop_time = loop_time;
    this->integral = 0;
    this->prior_error = 0;
    white_adjust = 0;
    black_adjust = 0;
}