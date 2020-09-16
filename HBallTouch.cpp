#include "HBallTouch.h"

//needed rename 1 because it included wrong header
#include <EEPROM1.h>

BallTouch::BallTouch(bool enabled, int threshhold)
{
    _enabled = enabled;
    if(threshhold != 0)
    {
        EEPROM.write(EEPROM_BALLTOUCH_THRESHOLD, threshhold);
    }
}

void BallTouch::init()
{
    _threshold = EEPROM.read(EEPROM_BALLTOUCH_THRESHOLD);
    _calibrated = false;
    if(_threshold <= 0)
        _calibrated = false;
    if(_enabled)
    {
        LogBalltouch("enabled");
        pinMode(BT_LED, OUTPUT);
        pinMode(BT_SENSOR, INPUT_PULLUP);
        LogBalltouch("Gets Threshold: " + _threshold);
        LogBalltouch("Intialized");
    } else 
        LogBalltouch("disabled");
}

void BallTouch::setCali(bool setCali)
{
    _calibrated = setCali;
}

const bool BallTouch::getCali()
{
    return _calibrated;
}

void BallTouch::calibrate()
{
    if(_enabled)
    {
    calibrateNoBall();

    while (millis() - _onTimer < 2000)
        digitalWrite(BT_LED, HIGH);
    digitalWrite(BT_LED, LOW);

    calibrateBall();
    calculateTreshold();
    }
}

void BallTouch::calibrateNoBall()
{

    _summe = 0;
    _counter = 0;
    //without Ball
    while (_counter < 20)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            _counter++;
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
            turnOn();
    }
    _thresholdNoBall = _summe / 20;
    digitalWrite(BT_LED, LOW);
    _state == LED_OFF;
}

void BallTouch::calibrateBall()
{
    _summe = 0;
    _counter = 0;

    //with ball
    while (_counter < 20)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            _counter++;
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
            turnOn();
    }
    _thresholdBall = _summe / 20;
    digitalWrite(BT_LED, LOW);
    _state == LED_OFF;
}

void BallTouch::calculateTreshold()
{
    if (_thresholdBall > -1)
    {
        if (_thresholdNoBall > -1)
        {
            _threshold = (_thresholdBall + _thresholdNoBall) / 2;
            _calibrated = true;
            if(_threshold <= 0)
                setCali(false);
            EEPROM.write(EEPROM_BALLTOUCH_THRESHOLD, _threshold);
            LogBalltouch("Sets threshold to: " + _threshold);
            LogBalltouch("Calibrated");
        }
    }
}

void BallTouch::update()
{
    if (_enabled)
    {
        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            calculate();
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
            calculate();
        }
    }else
        digitalWrite(BT_LED, LOW);
    
}

bool BallTouch::hasBall()
{
    if(_enabled)
    {
    LogBalltouch("Sees Ball: " + (_value > _threshold));    
    return _value > _threshold;
    }
    return 0;
}

void BallTouch::turnOn()
{
    _darkValue = analogRead(BT_SENSOR);
    digitalWrite(BT_LED, HIGH);
    _onTimer = millis();
    _state = LED_ON;
}

void BallTouch::turnOff()
{
    _lightValue = analogRead(BT_SENSOR);
    digitalWrite(BT_LED, LOW);
    _offTimer = millis();
    _state = LED_OFF;
}

void BallTouch::calculate()
{
    _value = (_darkValue - _lightValue);
}