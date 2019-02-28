#include <Arduino.h>
#include "Motor.h"
int dirPinLeft = 5;
int enablePinLeft = 4;
int dirPinRight = 2;
int enablePinRight = 3;

int sensorPinIn = 19;
Motor left_motor;
Motor right_motor;
void TestForKey(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("hello");
  pinMode(sensorPinIn, INPUT);
  left_motor = Motor(enablePinLeft, dirPinLeft, -1);
  right_motor = Motor(enablePinRight, dirPinRight, 1);
}

void loop() {
// put your main code here, to run repeatedly:
left_motor.setSpeed(150);
right_motor.setSpeed(150);
//Serial.println("hi");
//delay(100);
//Serial.println(analogRead(sensorPinIn)); //This and line below only test
//delay(500);
//TestForKey();
}

// void TestForKey(void){
//   uint8_t KeyEventOccurred;

//   KeyEventOccurred = Serial.available();
//   if (KeyEventOccurred) {
//     Serial.read();
//     dirPinStateRight = 1-dirPinStateRight;
//     dirPinStateLeft = 1-dirPinStateLeft;
//     digitalWrite(dirPinLeft, dirPinStateLeft);
//     digitalWrite(dirPinRight, dirPinStateRight);
//   }
// }
