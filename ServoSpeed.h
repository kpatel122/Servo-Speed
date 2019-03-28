/*
ServoSpeed.h non blocking variable servo speed control with STM32 on arduino
Copyright (c) 2019 Kunal Patel

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

This permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SERVOSPEED_H
#define SERVOSPEED_H

#include "Arduino.h"
#include <Servo.h>

 

          
class CServoSpeed
{
    public:
    bool attach(uint8 pin,
                uint16 minPulseWidth=SERVO_DEFAULT_MIN_PW,
                uint16 maxPulseWidth=SERVO_DEFAULT_MAX_PW,
                int16 minAngle=SERVO_DEFAULT_MIN_ANGLE,
                int16 maxAngle=SERVO_DEFAULT_MAX_ANGLE);
    
    void write(uint8 angle);

    void setSpeed(uint8 speed) {this->speed = speed;}

    void update(); //must be called once per loop

    bool moving() {return isMoving;}

    private:
    Servo servo;
    bool isMoving;
    bool positionSet;  
    bool waitingForDelay = false;
    unsigned long initialMillis;
    uint8 currentAngle;
    uint8 destinationAngle;
    uint8 speed;
};

#endif
