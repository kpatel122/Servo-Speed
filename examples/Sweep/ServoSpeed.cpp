/*
ServoSpeed.cpp non blocking variable servo speed control with STM32 on arduinp
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

#include "ServoSpeed.h"

bool CServoSpeed::attach(uint8 pin,
                uint16 minPulseWidth,
                uint16 maxPulseWidth,
                int16 minAngle,
                int16 maxAngle)
{
    bool res = servo.attach(pin,
                minPulseWidth,
                maxPulseWidth,
                minAngle,
                maxAngle);
    isMoving = false;
    positionSet = false;
    waitingForDelay = false;
    uint8 currentPos = 0;
    return res;
}

void CServoSpeed::write(uint8 angle)
{
    if(positionSet == false)
    {
        servo.write(angle);
        positionSet = true;
        currentAngle = angle; 
        destinationAngle = currentAngle;
        return;
    }

    destinationAngle = angle;
    isMoving = true;
}

void CServoSpeed::update()
{
    if(!isMoving || (currentAngle == destinationAngle) )
        return;

    short targetDelta = destinationAngle - currentAngle;    
    targetDelta = abs(targetDelta);

    if(destinationAngle > currentAngle)
    {
        if(waitingForDelay == false)
        {
            currentAngle = currentAngle + 1;
            servo.write(currentAngle);
            waitingForDelay = true;
            initialMillis = millis();

            //check if only wanted to move 1 degree
            if(currentAngle >= destinationAngle)
            {
                isMoving = false;
                return;
            }
        }
        else
        {
            if( (millis() - initialMillis) >= speed )
            {
                waitingForDelay = false;
                return;
            } 
        }
    }
    else if(destinationAngle < currentAngle)
    {
        if(waitingForDelay == false)
        {
            currentAngle = currentAngle - 1;
            servo.write(currentAngle);
            waitingForDelay = true;
            initialMillis = millis();

            if(currentAngle <= destinationAngle)
            {
                isMoving = false;
                return;
            }
        }
        else
        {
            if( (millis() - initialMillis) >= speed )
            {
                waitingForDelay = false;
                return;
            } 
        }
    }
}