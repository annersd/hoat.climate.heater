#pragma once

#include <Arduino.h>
#include <cobold.hpp>

/// @brief Controls a three-way valve
class ThreeWayValve
{
private:
    /* data */
cobold::actuators::IRelay* openHotRelay;
cobold::actuators::IRelay* openColdRelay;

public:
    ThreeWayValve(cobold::actuators::IRelay* openHotRelay, cobold::actuators::IRelay* openColdRelay);
    ~ThreeWayValve();
    void update();
    void moveToCold();
    void moveToCHot();
};

ThreeWayValve::ThreeWayValve(cobold::actuators::IRelay* openHotRelay, cobold::actuators::IRelay* openColdRelay)
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