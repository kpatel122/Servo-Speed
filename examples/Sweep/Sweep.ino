#include <ServoSpeed.h>

#define SERVO1_PIN PA7
#define SERVO2_PIN PA6
#define SERVO3_PIN PA1
#define SERVO4_PIN PA0

#define SERVOPIN SERVO4_PIN
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
    if(movingPos1 == true) //first position
    {
      servo.write(0);
      movingPos1 = false;
    }
    else
    {
      servo.write(180); //second position
      movingPos1 = true;
    }
  }
  servo.update();
}
