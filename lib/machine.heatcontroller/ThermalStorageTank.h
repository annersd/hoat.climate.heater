#pragma once

#include "cobold.hpp"

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
    std::vector<cobold::sensors::ITemperatureSensorOptions *> temperatureSensorOptions;
};