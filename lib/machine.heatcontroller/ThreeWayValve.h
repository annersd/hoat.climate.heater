#pragma once

#include <Arduino.h>
#include <cobold.hpp>
#include "SingleRelay.h"
#include "ThreeWayValveOptions.h"

/// @brief Controls a three-way valve
class ThreeWayValve
{
private:
    /* data */
cobold::actuators::IRelay* openHotRelay;
cobold::actuators::IRelay* openColdRelay;

ServiceCollection *services;
ILogger *logger;

public:
    ThreeWayValve(ServiceCollection *services, ThreeWayValveOptions options);
    ~ThreeWayValve();
    void update();
    void moveToCold();
    void moveToHot();
};

ThreeWayValve::ThreeWayValve(ServiceCollection *services, ThreeWayValveOptions options)
{
    this->services = services;
    this->logger = services->getService<ILogger>();
    this->openHotRelay = new SingleRelay(services, options.getHotPin());
    this->openColdRelay = new SingleRelay(services, options.getColdPin());
}

ThreeWayValve::~ThreeWayValve()
{
}

void ThreeWayValve::update()
{

}

void ThreeWayValve::moveToCold(){

}

void ThreeWayValve::moveToHot(){

}