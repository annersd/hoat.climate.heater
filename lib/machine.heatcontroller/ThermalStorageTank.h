#pragma once

#include "Cobold.hpp"
#include "cobold_new.hpp"
#include "ITemperatureSensor.h"

class ThermalStorageTank
{
private:
    // List of ITemperatureSensor
    std::vector<cobold::sensors::ITemperatureSensor *> temperatureSensors;

public:
    ThermalStorageTank(cobold::sensors::ITemperatureSensor *temperatureSensor);
    ~ThermalStorageTank();
    void update();

    std::vector<cobold::sensors::ITemperatureSensor *> getTemperatureSensors()
    {
        return temperatureSensors;
    }
};

// Options for the thermal storage tank

class ThermalStorageTankOptions
{   
private:
    // std::vector<cobold::sensors:: *> temperatureSensorOptions;
};