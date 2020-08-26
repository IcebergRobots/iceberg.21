#pragma once

#include "SPlayer.h"

class Test : public Player
{
public:
    Player* update() override;
    void play() override;

private:
};