#pragma once

#include "Config.h"
#include "Hardware.h"

#include <Pixy.h>

#define SIG_BALL 1
#define SIG_GOAL 2

class Camera : private Pixy, public Hardware
{
public: 
    Camera(const bool& enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;

    inline bool seesBall() { return _ballPos != 0; }

    inline int getBArea() { return _ballArea; }
    inline int getBPos() { return _ballPos; }
    inline int getGArea() { return _goalArea; }
    inline int getGWidth() { return _goalWidth; }

private:
    int _blockCount = 0;
    int _ballCount = 0;
    int _goalCount = 0;

    int _ballHeight = 0;
    int _ballWidth = 0;
    int _ballArea = 0;
    int _ballPos = 0;

    int _goalHeight = 0;
    int _goalWidth = 0;
    int _goalArea = 0;
    int _goalPos = 0;
    unsigned long _timer = 0;
    
};


