#include "HKick.h"

void Kick::init()
{
    if (_enabled)
    {
        LogKick("enabled");
        pinMode(KICKER, OUTPUT);
        LogKick("Initilized");
    }else   
        LogKick("disabled");
}

void Kick::update()
{
    if (_enabled && millis() - _timer > 50)
        analogWrite(KICKER, 0);
}

void Kick::kick()
{
    if (_enabled && _calibrated && millis() - _timeout > _delay)
    {
        _timer = millis();
        _timeout = millis();
        analogWrite(KICKER, _power); // schuss bei 12, Poti bei A0
    }
 }
 
 void Kick::setCali(bool caliKick)
 {
     _calibrated = caliKick;
 }

 void Kick::setPower(unsigned int power)
 {
     _power = power;
     _calibrated = true;
 }