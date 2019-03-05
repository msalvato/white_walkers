#include <Arduino.h>
#include <Metro.h>
#include <Servo.h>
#include "OurServo.h"

uint8_t testupdateDelayTimer(void);
void updateDelayExp(void);
void testForKey(void);
void Counter(void);

OurServo::OurServo() {

}

OurServo::OurServo(int servo_pin) {
    this->myservo.attach(servo_pin);
}

void OurServo::changeDirExp (void){
  this->increment = -this->increment;
  this->pos += this->increment;
  this->end = 0;
}

int OurServo::runServo(){
  if(this->updateDelay.check()){
      updateDelayExp();
  }
  return this->numCycles;
}

void OurServo::resetServo() {
  pos = 1;
  increment = -1;
  end = 0;
  count = 0;
  changeDir.reset();
  updateDelay.reset();
}

void OurServo::updateDelayExp(){
  // Starting timer to pause motor at the end to give time to get there
  if ((pos == maxAng || pos == 0) && end == 0 && count != maxRev){
    changeDir.reset();
    end  = 1;
  }

  // Change direction of motor
  if (this->changeDir.check()) this->changeDirExp();

  // Incrementing position of motor
  if (pos < maxAng && pos > 0){
    pos += increment;
  }

  // Stopping motor when it reaches the number of desired cycles
  if (count == maxRev){
    pos = 0;
  } 
  
  // Counting the number of cycles done
  if (pos == 1){
    this->numCycles++;
  }

  myservo.write(pos);
  this->updateDelay.reset();
  //Serial.println(pos);
}