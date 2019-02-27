#include <Arduino.h>

int potPin = 20;
int dirPinLeft = 5;
int enablePinLeft = 4;
int dirPinRight = 2;
int enablePinRight = 3;
int sensorPinIn = 19;
int motorSpeed = 0;
uint16_t dirPinStateLeft = HIGH;
uint16_t dirPinStateRight = LOW;

void TestForKey(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("hello");
  pinMode(potPin, INPUT);
  pinMode(dirPinLeft, OUTPUT);
  pinMode(dirPinRight, OUTPUT);
  pinMode(enablePinLeft, OUTPUT);
  pinMode(enablePinRight, OUTPUT);
  pinMode(sensorPinIn, INPUT);
  digitalWrite(dirPinLeft,dirPinStateLeft);
  digitalWrite(dirPinRight,dirPinStateRight);
}

void loop() {
// put your main code here, to run repeatedly:
analogWrite(enablePinLeft, motorSpeed);
analogWrite(enablePinRight, motorSpeed);
//Serial.println("hi");
delay(100);
Serial.println(analogRead(sensorPinIn)); //This and line below only test
//delay(500);
//TestForKey();
}

void TestForKey(void){
  uint8_t KeyEventOccurred;

  KeyEventOccurred = Serial.available();
  if (KeyEventOccurred) {
    Serial.read();
    dirPinStateRight = 1-dirPinStateRight;
    dirPinStateLeft = 1-dirPinStateLeft;
    digitalWrite(dirPinLeft, dirPinStateLeft);
    digitalWrite(dirPinRight, dirPinStateRight);
  }
}
