#pragma once

#include "Config.h"
#include "Hardware.h"

#define FILTER_VALUES 5
//Datasheet: http://coecsl.ece.illinois.edu/ge423/DevantechSRF08UltraSonicRanger.pdf

class Ultrasonic : public Hardware
{
public:
    Ultrasonic(const bool& enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;


    inline int getFrontLeft() { return _filteredDistance[0]; }
    inline int getLeft() { return _filteredDistance[1]; }
    inline int getBack() { return _filteredDistance[2]; }
    inline int getRight() { return _filteredDistance[3]; }
    inline int getFrontRight() { return _filteredDistance[4]; }
    inline int getFront() { return min(getFrontLeft(), getFrontRight()); }


private:
    void filter();
    void fetch();
    bool _fetched = true;

    unsigned long _lastMeasurement = 0;
    const uint8_t _addresses[NUM_OF_US] = {FRONT_LEFT, LEFT, BACK, RIGHT, FRONT_RIGHT}; //vorher progmen, um im flash(langsamer) und nicht im sram zu speichern, braucht bestimmte funktionen um wert auszulesen, diese wurden nicht benutzt
    int _distance[NUM_OF_US][FILTER_VALUES] = {{-1, -1, -1, -1, -1},{-1, -1, -1, -1, -1},{-1, -1, -1, -1, -1},{-1, -1, -1, -1, -1},{-1, -1, -1, -1, -1}};
    int _filteredDistance[NUM_OF_US] = {-1, -1, -1, -1, -1};
};