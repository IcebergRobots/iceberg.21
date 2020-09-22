#include "Config.h"

#include "HUltrasonic.h"
#include "HMotor.h"
#include "HChassis.h"
#include "HBallTouch.h"
#include "HKick.h"
#include "HCamera.h"

#include "SStandby.h"
#include "STest.h"

#include "Utility.h"

Camera camera(ENDISABLE_CAMERA);
Kick kick(ENDISABLE_KICK, 255);
BallTouch bt(ENDISABLE_BALLTOUCH);
Ultrasonic us(ENDISABLE_ULTRASONIC);

Motor motors[] = {
    Motor(FWD0, BWD0, PWM0, M0_CURR),
    Motor(FWD1, BWD1, PWM1, M1_CURR), 
    Motor(FWD2, BWD2, PWM2, M2_CURR), 
    Motor(FWD3, BWD3, PWM3, M3_CURR)
};
Chassis chassis(motors, 4, ENDISABLE_CHASSIS);


Hardware *hardwares[] = { &us , &chassis, &bt, &kick, &camera };

Player* state;
Standby sStandby;
Test sTest;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    for(Hardware* hardware : hardwares)
        hardware->init();

    getRobot();
    startSound();

    state = &sStandby;

    LogUtility("Free Ram: " + getFreeSRAM());
    bt.calibrate();
}

void loop() 
{
    for(Hardware* hardware : hardwares)
        hardware->update();

    //state = state->update();
    //state->play();
    if(camera.seesBall())
        chassis.drive(map(camera.getBPos(), 1, 315, 90, -90), 50);
    else
        chassis.brake(true);
        
    if(bt.hasBall())
        kick.kick();

    LogCam("Ballposition " + camera.getBPos());
    LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft() + "  FL: " + us.getFrontLeft() + "  FR: " + us.getFrontRight());
}