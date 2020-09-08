#include "Config.h"

#include "HUltrasonic.h"
#include "HMotor.h"
#include "HChassis.h"

#include "SStandby.h"
#include "STest.h"


Ultrasonic us(ENDISABLE_ULTRASONIC);

Motor motors[] = {
    Motor(FWD0, BWD0, PWM0, M0_CURR),
    Motor(FWD1, BWD1, PWM1, M1_CURR), 
    Motor(FWD2, BWD2, PWM2, M2_CURR), 
    Motor(FWD3, BWD3, PWM3, M3_CURR)
};
Chassis chassis(motors, 4, ENDISABLE_CHASSIS);


Hardware *hardwares[] = { &us , &chassis};

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

    chassis.getMotor(0).setEn(false);
}

void loop() 
{
    for(Hardware* hardware : hardwares)
        hardware->update();

    chassis.drive(0, 50);
    //state = state->update();
    //state->play();

    LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft() + "  FL: " + us.getFrontLeft() + "  FR: " + us.getFrontRight());

}