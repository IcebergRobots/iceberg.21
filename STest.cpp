#include "STest.h"

#include "HardwareSerial.h"

#include "SStandby.h"

extern Standby sStandby;

Player* Test::update()
{
    if(Serial.available() > 0)
    {
        int input = Serial.read();
        if((char)input == '2')
        {
            Serial.println("Already in Test");
            return this;
        } else if((char)input == '1')
        {
            Serial.println("Changed to Standby");
            return &sStandby;
        }
    }
    return this;
}

void Test::play()
{
   // Serial.println("Test play");
}