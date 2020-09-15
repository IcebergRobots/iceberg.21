#pragma once
#include "Config.h"
#include "Hardware.h"


#define LED_OFF false
#define LED_ON true

class BallTouch : public Hardware
{

public:
    BallTouch(bool enabled = false, int threshhold = 0);
    void init() override;
    void update() override;

    void calibrate();

    //only call this in combination
    void calibrateNoBall();
    void calibrateBall();
    void calculateTreshold();
    
    // const bool getCaliNoBall();
    // const bool getCaliBall();
    void setCali(bool setCali);
    const bool getCali();

    inline int getValue() { return _value; }
    inline int getThreshold() { return _threshold; }
    inline int getBallThreshold() { return _thresholdBall; }
    inline int getNoBallThreshold() { return _thresholdNoBall; }
    bool hasBall();

private:
    int _thresholdNoBall = -1;
    int _thresholdBall = -1;
    int _threshold;

    bool _calibrated;
    
    int _summe;
    int _counter;

    int _value;
    int _darkValue;
    int _lightValue;

    unsigned long _offTimer;
    unsigned long _onTimer;

    bool _state = LED_OFF;

    void turnOn();
    void turnOff();
    void calculate();
};

