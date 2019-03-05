#include "StateMachine.h"

StateMachine::StateMachine() {

}

StateMachine::StateMachine(LineFollow to_armory, LineFollow to_kings, AlignLauncher align_kings, BumpSensor bump_sensor, Motor left_motor, Motor right_motor){
    this->to_armory = to_armory;
    this->to_kings = to_kings;
    this->align_kings = align_kings;
    this->bump_sensor = bump_sensor;
    this->left_motor = left_motor;
    this-> right_motor = right_motor;
}

void StateMachine::setStart(State start_state) {
    this->current_state = start_state;
}
void StateMachine::machineLoop() {
    switch(this->current_state) {
        case toarmory:
            this->to_armory.drive();
            if (this->bump_sensor.checkSensor()){
                this->current_state = hitbump;
                lever_timer.reset();
                left_motor.setSpeed(-150);
            }
            break;
        case hitbump:
            if (lever_timer.check()) {
                this->current_state = loadballs;
                load_timer.reset();
                left_motor.setSpeed(150);
            }
            break;
        case loadballs:
            if (this->bump_sensor.checkSensor()){
                left_motor.setSpeed(0);
            }
            if (load_timer.check()){
                this->current_state = tokings;
                ignore_blue_tape.reset();
            }
            break;
        case tokings:
            this->to_kings.drive();
            if (ignore_blue_tape.check()){

            }
            if (align_kings.checkCrossedCross()) {
                this->current_state = launching;
                this->right_motor.setSpeed(0);
                this->left_motor.setSpeed(0);
            }
            break;
        case aligningkings:
            //align_kings.alignWithCross(to_kings, to_armory);
            break;
        case launching:
            
        
    }
}