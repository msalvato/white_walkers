#ifndef OurServo_h
#define OurServo_h

#include <Arduino.h>
#include <Servo.h>
#include <Metro.h>


class OurServo
{

public:
  OurServo();
  OurServo(int servo_pin, int updateDelay, int maxAng);
  void updateDelayExp();
  int runServo();
  void changeDirExp();
  void resetServo();
  int pos = 1;
	
private:
  Metro updateDelay = Metro(20); // How long to wait so that the motor can get there
  Servo myservo;
  //int maxRev = 6;
  int maxAng = 160;
  int numCycles = 0;
  int increment = -1;
  bool end = 0;
  int count = 0;
};

#endif