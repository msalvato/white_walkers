#ifndef OurServo_h
#define OurServo_h

#include <Arduino.h>
#include <Servo.h>
#include <Metro.h>


class OurServo
{

public:
  OurServo();
  OurServo(int servo_pin);
  void updateDelayExp();
  int runServo();
  void changeDirExp();
  void resetServo();
	
private:
  Metro updateDelay = Metro(20); // How long to wait so that the motor can get there
  //Metro changeDir = Metro(2000); // How long to wait before changing directions
  Servo myservo;
  int maxRev = 6;
  int maxAng = 160;
  int numCycles = 0;
  int pos = 1;
  int increment = -1;
  bool end = 0;
  int count = 0;
};

#endif