#pragma once

#include "Config.h"
#include "Hardware.h"

class Kick : public Hardware
{
    public:
        Kick(const bool& enabled = false, int power = 0)
        {
            _enabled = enabled;
            setPower(power); //sets calibrated man könnte sonst initializer lists benutzen
        };
        void init() override;
        void update() override;

        void kick();

        void setCali(bool calibrated);
        inline const bool getCali() const { return _calibrated; };

        void setPower(unsigned int kickPower);
        inline const int getPower() const { return _power; };
    private:
        bool _calibrated = false;

        const int _delay = 400; // in ms 

        unsigned long _timer = 0;   //wie lange der kicker an ist
        unsigned long _timeout = 0; //wie lange das delay zwischen den kicks ist
        unsigned int _power = 0;
};