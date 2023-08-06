#ifndef HEAT_CIRCUIT_H
#define HEAT_CIRCUIT_H

#include <Arduino.h>
#include "ThreeWayValve.h"
#include "Thermistor.h"


class HeatCircuit {
private:
  Thermistor thermistor;
  int relayPin;
  float targetTemperature;
  ThreeWayValve threeWayValve;

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
  HeatCircuit(int thermistorPin, int relayPin, float targetTemp)
      : thermistor(thermistorPin), relayPin(relayPin), targetTemperature(targetTemp) {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
  }

  void controlHeating() {

    float currentTemp = thermistor.readTemperature();

    if (currentTemp < targetTemperature) {
      digitalWrite(relayPin, HIGH);
    } else {
      digitalWrite(relayPin, LOW);
    }
  }

  void update(float currentOutsideTemp) {
    float desiredIndoorTemp = heatingCurve(currentOutsideTemp);
    targetTemperature = desiredIndoorTemp;
    controlHeating();
  }
};

#endif // !HEAT_CIRCUIT_H