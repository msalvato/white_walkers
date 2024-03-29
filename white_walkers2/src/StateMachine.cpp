#include "StateMachine.h"

StateMachine::StateMachine() {

}

StateMachine::StateMachine(LineFollow to_armory, LineFollow to_kings, AlignLauncher align_kings, BumpSensor bump_sensor, Motor left_motor, Motor right_motor, OurServo servo, OurServo gate){
    this->to_armory = to_armory;
    this->to_kings = to_kings;
    this->align_kings = align_kings;
    this->bump_sensor = bump_sensor;
    this->left_motor = left_motor;
    this-> right_motor = right_motor;
    this->gate = gate;
    this->servo = servo;
}

void StateMachine::setStart(State start_state) {
    this->current_state = start_state;
}
void StateMachine::machineLoop() {
    int gate_test_count;
    int servo_test_count;

    switch(this->current_state) {
        case toarmory:
            this->to_armory.drive();
            if (this->bump_sensor.checkSensor()){
                this->current_state = hitbump;
                lever_timer.reset();
                right_motor.setSpeed(0);
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
                this->current_state = tokings;
                ignore_blue_tape.reset();
                blue_tape_timer = 0;
            }
            break;
        case tokings:
            this->to_kings.drive();
            if (ignore_blue_tape.check()) {
                blue_tape_timer = 1;
            }
            if (blue_tape_timer){
                if (align_kings.checkCrossedCross()) {
                    this->current_state = launching;
                    this->right_motor.setSpeed(0);
                    this->left_motor.setSpeed(0);
                    align_kings.crossed_cross = 0;
                    servo_current_count = 0;
                    gate_current_count = 0;
                }
            }
            break;
        
        case launching:
            servo_test_count = servo.runServo();
            if (servo_test_count == 4) { //balls to launch minus 1
                this->current_state = toarmory;
                servo.resetServo();
                gate.resetServo();
            }
            else if (servo_test_count > servo_current_count) {
                servo_current_count = servo_test_count;
                this->current_state = resetgate;
            }
            break;
        case resetgate:
            gate_test_count = this->gate.runServo();
            if (gate_test_count > gate_current_count) {
                gate_current_count = gate_test_count;
                this->current_state = launching;
            }
            break;

    }
}