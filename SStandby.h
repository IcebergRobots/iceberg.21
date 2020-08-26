#pragma once

#include "SPlayer.h"

class Standby : public Player
{
public:
    Player* update() override;
    void play() override;

private:
};