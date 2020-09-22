#pragma once

#include "Config.h"

void startSound();
void reset();
void heartbeat();
uint16_t getFreeSRAM();

enum class Robot
{
    A, B
};
Robot getRobot(); 