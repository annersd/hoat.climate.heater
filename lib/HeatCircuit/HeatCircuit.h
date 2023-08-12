#ifndef HEAT_CIRCUIT_H
#define HEAT_CIRCUIT_H

#include <Arduino.h>
#include "ThreeWayValve.h"
#include "ITemperatureSensor.h"
#include "IComponent.h"
#include "IRelay.h"

class HeatCircuit : public IComponent
{
private:
  ITemperatureSensor *temperatureSensor;
  float targetTemperature; 
  ThreeWayValve *threeWayValve;
  IRelay *waterPump;

  float hysteresis; // Private member for hysteresis value

  float heatingCurve(float currentOutsideTemp)
  {
    // Implement the heating curve calculation based on the outside temperature.
    // Adjust this function to fit your specific heating requirements.
    const float desiredIndoorTempAtZero = 21.0;
    const float heatingSlope = 0.5;

    float desiredIndoorTemp = desiredIndoorTempAtZero + (currentOutsideTemp * heatingSlope);
    return desiredIndoorTemp;
  }

public:
  HeatCircuit(ITemperatureSensor *hcTemeraturSensor, ThreeWayValve *threeWayValve, IRelay *waterPump, float targetTemp)
      : temperatureSensor(hcTemeraturSensor),
        targetTemperature(targetTemp),
        threeWayValve(threeWayValve),
        waterPump(waterPump)
  {
  }

  void controlHeating()
  {
    float currentTemp = temperatureSensor->getTemperatureCelsius();

    // Apply hysteresis around the target temperature
    if (currentTemp < targetTemperature - 10.0)
    {
      threeWayValve->moveToCHot();
    }
    else if (currentTemp > targetTemperature + 10.0)
    {
      threeWayValve->moveToCold();
    }

    // Ensure the absolute maximum temperature is not exceeded
    if (currentTemp > 70.0)
    {
      threeWayValve->moveToCold(); // Move to cold to prevent overheating
    }

    // Turn on the water pump if the current temperature is below the target temperature minus 0.5 degrees
    if (currentTemp < targetTemperature - 0.5)
    {
      waterPump->open();
    }
    else
    {
      waterPump->close();
    }
  }

  void setOutsideTemperatue(float currentOutsideTemp)
  {
    float desiredIndoorTemp = heatingCurve(currentOutsideTemp);
    targetTemperature = desiredIndoorTemp;
  }

  void initialize() override
  {
    waterPump->close();
  }

  void update() override
  {
    controlHeating();
  }

   // Getter method for hysteresis
  float getHysteresis() const
  {
    return hysteresis;
  }

  // Setter method for hysteresis
  void setHysteresis(float value)
  {
    hysteresis = value;
  }
};

#endif // !HEAT_CIRCUIT_H