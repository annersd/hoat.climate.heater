#pragma once

#include "ThreeWayValveOptions.h"

/**
 * @brief Options for the heat circuit components
 *
 * @details
 * This class is used to configure the heat circuit components.
 * It contains the options for the thermistor, pump relay, target temperature, and three-way valve.
 */
class HeatCircuitOptions
{
public:
    HeatCircuitOptions(int thermistorPin, int pumpRelayPin,
                                 float targetTemperature, float maxSystemTemparature,
                                 ThreeWayValveOptions threeWayValveOptions)
        : thermistorPin(thermistorPin),
          pumpRelayPin(pumpRelayPin),
          targetTemperature(targetTemperature),
          maxSystemTemperature(maxSystemTemparature),
          threeWayValveOptions(threeWayValveOptions)
    {
    }

    HeatCircuitOptions()
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

    float getMaxSystemTemperature() const
    {
        return maxSystemTemperature;
    }

    void setMaxSystemTemperature(float temp)
    {
        maxSystemTemperature = temp;
    }

private:
    int thermistorPin;
    int pumpRelayPin;
    float targetTemperature;
    ThreeWayValveOptions threeWayValveOptions;
    float maxSystemTemperature;
};
