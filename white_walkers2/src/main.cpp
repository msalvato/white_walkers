#include <Arduino.h>

int potPin = 20;
int dirPinLeft = 8;
int enablePinLeft = 9;
int dirPinRight = 17;
int enablePinRight = 16;
int sensorPinIn = 18;
int potRead = 128;
uint16_t dirPinStateLeft = 0;
uint16_t dirPinStateRight = 0;

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
  digitalWrite(dirPinLeft,HIGH);
  digitalWrite(dirPinRight,HIGH);
}

void loop() {
// put your main code here, to run repeatedly:
//potRead = analogRead(potPin);
//potRead = map(potRead, 0, 1023, 0, 255);
//analogWrite(enablePinLeft, potRead);
//analogWrite(enablePinRight, potRead);
Serial.println(analogRead(sensorPinIn));
delay(500);
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
