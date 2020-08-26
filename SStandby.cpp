#include "SStandby.h"
#include "HardwareSerial.h"

#include "STest.h"

extern Test sTest;

Player* Standby::update()
{
    if(Serial.available() > 0)
    {
        int input = Serial.read();
        if((char)input == '1')
        {
            Serial.println("Already in Standby");
            return this;
        } else if((char)input == '2')
        {
            Serial.println("Changed to Test");
            return &sTest;
        }
    }
    return this;
}

void Standby::play()
{
   // Serial.println("Standby play");
}