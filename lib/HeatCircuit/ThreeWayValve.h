#pragma once

#include <Arduino.h>
#include <abstractions.hpp>

/// @brief Controls a three-way valve
class ThreeWayValve
{
private:
    /* data */
abstractions::actuators::IRelay* openHotRelay;
abstractions::actuators::IRelay* openColdRelay;

public:
    ThreeWayValve(abstractions::actuators::IRelay* openHotRelay, abstractions::actuators::IRelay* openColdRelay);
    ~ThreeWayValve();
    void update();
    void moveToCold();
    void moveToCHot();
};

ThreeWayValve::ThreeWayValve(abstractions::actuators::IRelay* openHotRelay, abstractions::actuators::IRelay* openColdRelay)
{
    this->openHotRelay = openHotRelay;
    this->openColdRelay = openColdRelay;
}

ThreeWayValve::~ThreeWayValve()
{
}

void ThreeWayValve::update()
{

}

void ThreeWayValve::moveToCold(){

}

void ThreeWayValve::moveToCHot(){

}