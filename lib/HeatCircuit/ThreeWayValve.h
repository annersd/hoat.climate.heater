#ifndef THREE_WAY_MIXER_H
#define THREE_WAY_MIXER_H

#include <Arduino.h>
#include <IRelay.h>

/// @brief Controls a three-way valve
class ThreeWayValve
{
private:
    /* data */
IRelay* openHotRelay;
IRelay* openColdRelay;

public:
    ThreeWayValve(IRelay* openHotRelay, IRelay* openColdRelay);
    ~ThreeWayValve();
    void update();
    void moveToCold();
    void moveToCHot();
};

ThreeWayValve::ThreeWayValve(IRelay* openHotRelay, IRelay* openColdRelay)
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
#endif // !THREE_WAY_MIXER_H
