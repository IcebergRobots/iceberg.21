#pragma once

#include "Config.h"
#include "Hardware.h"

class Motor : public Hardware
{
public:
    Motor(uint8_t fwd, uint8_t bwd, uint8_t pwm, int curSens)
       : _fwd(fwd), _bwd(bwd), _pwm(pwm), _curSens(curSens), _power(0) {}
    void init() override;
    void update() override; //TODO Encodersignals
    void setEn(const bool& enabled) override;
    
    void steerMotor();
    void brake(const bool& active);
    void setPower(int power);
private:
    uint8_t _fwd;
    uint8_t _bwd;
    uint8_t _pwm;
    int _curSens;
    
    int _power;
    
};