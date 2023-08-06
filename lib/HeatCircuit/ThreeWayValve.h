#ifndef THREE_WAY_MIXER_H
#define THREE_WAY_MIXER_H

#include <Arduino.h>
#include "SingleRelay.h"

/// @brief Controls a three-way valve
class ThreeWayValve
{
private:
    /* data */
SingleRelay openHotRelay;
SingleRelay openColdRelay;

public:
    ThreeWayValve(/* args */);
    ~ThreeWayValve();
    void update();
};

ThreeWayValve::ThreeWayValve(/* args */)
{
}

ThreeWayValve::~ThreeWayValve()
{
}

void ThreeWayValve::update()
{
    openHotRelay.turnOn();
    openColdRelay.turnOff();
}

#endif // !THREE_WAY_MIXER_H
