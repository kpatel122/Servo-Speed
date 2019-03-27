#include "ServoSpeed.h"

#define SERVOPIN PA0
CServoSpeed servo;
int servoSpeed = 15;
bool movingPos1 = true; //movingPosition1 is 180. after 180 reset the position to 0

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVOPIN);
  servo.setSpeed(servoSpeed);
  servo.write(90); //first write cant be speed controlled, so set initial position in setup
  
  servo.write(180); //all sebsequent calls can be speed controlled
}

void loop() {
  // put your main code here, to run repeatedly:
  if(servo.moving() == false)
  {
    if(movingPos1 == true)
    {
      servo.write(0);
      movingPos1 = false;
    }
    else
    {
      servo.write(180);
      movingPos1 = true;
    }
  }
  servo.update();
}
