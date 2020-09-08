#pragma once

#include "Wire.h"

class Hardware {
    public:
        virtual void init() = 0;
        virtual void update() = 0;

        virtual void setEn(const bool& enabled);
        virtual const bool getEn();
    protected:
        bool _enabled = true;
};