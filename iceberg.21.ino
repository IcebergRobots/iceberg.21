
#include "Config.h"
#include "Ultrasonic.h"
#include "SStandby.h"
#include "STest.h"


Ultrasonic us(ENDISABLE_ULTRASONIC);
Hardware *hardwares[] = { &us };

Player* state;
Standby sStandby;
Test sTest;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    state = &sStandby;

    for(Hardware* hardware : hardwares)
        hardware->init();
}

void loop() 
{
    for(Hardware* hardware : hardwares)
        hardware->update();

    //state = state->update();
    //state->play();

    LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft() + "  FL: " + us.getFrontLeft() + "  FR: " + us.getFrontRight());

}