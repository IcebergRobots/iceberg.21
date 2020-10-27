#pragma once

#include "Config.h"

void startSoundA();
void startSoundB();
void reset();
void heartbeat();
uint16_t getFreeSRAM();

enum class Robot
{
    A, B
};
Robot getRobot(); 