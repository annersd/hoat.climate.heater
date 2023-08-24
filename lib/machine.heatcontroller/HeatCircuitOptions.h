#pragma once

#include "ThreeWayValveOptions.h"

class HeatCircuitComponentsOptions
{
public:
    HeatCircuitComponentsOptions(int thermistorPin, int pumpRelayPin, int targetTemperature, ThreeWayValveOptions threeWayValveOptions)
        : thermistorPin(thermistorPin),
          pumpRelayPin(pumpRelayPin),
          targetTemperature(targetTemperature),
          threeWayValveOptions(threeWayValveOptions)
    {
    }

    HeatCircuitComponentsOptions()
    {
        thermistorPin = -1;
        pumpRelayPin = -1;
        targetTemperature = 0.0;
    }

    int getThermistorPin() const
    {
        return thermistorPin;
    }

    void setThermistorPin(int pin)
    {
        thermistorPin = pin;
    }

    int getPumpRelayPin() const
    {
        return pumpRelayPin;
    }

    void setPumpRelayPin(int pin)
    {
        pumpRelayPin = pin;
    }

    void setTargetTemperature(float temp)
    {
        targetTemperature = temp;
    }

    float getTargetTemperature() const
    {
        return targetTemperature;
    }

    ThreeWayValveOptions getThreeWayValveOptions() const
    {
        return threeWayValveOptions;
    }

    void setThreeWayValveOptions(ThreeWayValveOptions options)
    {
        threeWayValveOptions = options;
    }

private:
    int thermistorPin;
    int pumpRelayPin;
    float targetTemperature;
    ThreeWayValveOptions threeWayValveOptions;
};
