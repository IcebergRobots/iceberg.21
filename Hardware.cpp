#include "Hardware.h"

void Hardware::setEn(bool enabled)
{
    _enabled = enabled;
}

const bool Hardware::getEn()
{
    return _enabled;
}