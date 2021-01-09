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
#ifdef ESP32
#include <ESP32Servo.h>
#else
	#include <Servo.h>
#endif


 


          
class CServoSpeed
{
    public:
    bool attach(uint8_t pin);
    
    void write(uint8_t angle);

    void setSpeed(uint8_t speed) {this->speed = speed;}

    void update(); //must be called once per loop

    bool moving() {return isMoving;}

    private:
    Servo servo;
    bool isMoving;
    bool positionSet;  
    bool waitingForDelay = false;
    unsigned long initialMillis;
    uint8_t currentAngle;
    uint8_t destinationAngle;
    uint8_t speed;
};

#endif
