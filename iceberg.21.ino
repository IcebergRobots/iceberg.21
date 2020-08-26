
#include "HardwareSerial.h"
#include "SStandby.h"
#include "STest.h"

Player* state;
Standby sStandby;
Test sTest;

void setup()
{
    Serial.begin(9600);
    state = &sStandby;
}

void loop() 
{
    state = state->update();
    state->play();
}