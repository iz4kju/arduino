#include <math.h>
#include<Servo.h>
#include "Wire.h"
#include "WiiChuck.h"
#define MAXANGLE 90
#define MINANGLE -90

Servo myservo;
Servo myservo2;
Servo myservo3;
Servo myservo4;
WiiChuck chuck = WiiChuck();
int angleStart, currentAngle;
int tillerStart = 0;
double angle;
float power=0.0;

void setup() {
  Serial.begin(115200);
  myservo.attach(A1);
  myservo.write(50);
  myservo2.attach(A3);
  myservo2.write(50);
  myservo3.attach(A2);
  myservo3.write(50);
  myservo4.attach(A0);
  myservo4.write(50);
  chuck.begin();
  chuck.update();
}

void loop() {
  chuck.update();
  myservo.write((chuck.readRoll()+140)/1.5);
  myservo2.write((chuck.readPitch()+300)/4);
  myservo3.write((chuck.readJoyY()+195)/2);
  myservo4.write((chuck.readJoyX()+190)/2);
}
