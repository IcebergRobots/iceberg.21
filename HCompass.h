#pragma once

#include "Config.h"
#include "Hardware.h"

#include <Adafruit_BNO055.h>

class Compass : public Hardware
{
public:    
    Compass(bool enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;

    void cali();
    inline int getAngle() { return _angle; };
    int getPitch() { return _pitch; };
    int getRoll() { return _roll; };

private:
    int _angle = 0;
    int _pitch = 0;
    int _roll = 0;

    unsigned long _lastTime = 0.0f; // for delay between measurements

    bool _calsystem = false, _calgyro = false, _calaccel = false, _calmag = false;
// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
    Adafruit_BNO055 bno;
};