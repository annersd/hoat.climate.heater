#pragma once

#include <Arduino.h>
#include <cobold.hpp>
#include "ThreeWayValve.h"
#include "HeatCircuitOptions.h"

/**
 * @brief Controls the heat circuit
 * 
 * @details
 * This class is used to control the heat circuit.
 * It contains the logic for controlling the three-way valve and water pump.
*/
class HeatCircuit : public cobold::components::IComponent
{
private:
  HeatCircuitOptions options;

  cobold::sensors::ITemperatureSensor *temperatureSensor;
  float targetTemperature; 
  float maxSystemTemperature;
  ThreeWayValve *threeWayValve;
  cobold::actuators::IRelay *waterPump;

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
  HeatCircuit(cobold::sensors::ITemperatureSensor *hcTemeraturSensor, ThreeWayValve *threeWayValve, 
  cobold::actuators::IRelay *waterPump, float targetTemp, float maxSystemTemp)
      : temperatureSensor(hcTemeraturSensor),
        targetTemperature(targetTemp),
        maxSystemTemperature(maxSystemTemp),
        threeWayValve(threeWayValve),
        waterPump(waterPump)
  {
    
  }

  void controlHeating()
  {
    // Read the current feeder temperature
    float currentTemp = temperatureSensor->getTemperatureCelsius();

    // Apply hysteresis around the target temperature
    if (currentTemp < targetTemperature - 10.0)
    {
      threeWayValve->moveToHot(2.0F);
    }
    else if (currentTemp > targetTemperature + 10.0)
    {
      threeWayValve->moveToCold(2.0F);
    }

    // Ensure the absolute maximum temperature is not exceeded
    if (currentTemp > maxSystemTemperature)
    {
      threeWayValve->moveToCold(5.0F); // Move to cold to prevent overheating
    }

    // Turn on the water pump if the current temperature is below the target 
    // temperature minus 0.5 degrees Celsius. This is to prevent the pump from
    // switching on and off too often.
    if (currentTemp < targetTemperature - 0.5)
    {
      waterPump->open();
    }
    else
    {
      waterPump->close();
    }
  }
  
  /**
   * Set the target temperature based on the current outside temperature.
  */
  void setOutsideTemperatue(float currentOutsideTemp)
  {
    float desiredIndoorTemp = heatingCurve(currentOutsideTemp);
    targetTemperature = desiredIndoorTemp;
  }

  /**
   * Initialize the heat circuit.
   * This method is called once when the system is started.
  */
  void initialize() override
  {
    waterPump->close();

    // move the valve to cold to ensure the valve is in a known state
    threeWayValve->moveToCold( 10.0F );
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
