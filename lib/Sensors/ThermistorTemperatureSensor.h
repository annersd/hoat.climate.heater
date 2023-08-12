#ifndef THERMISTOR_TEMPERATURE_SENSOR_H
#define THERMISTOR_TEMPERATURE_SENSOR_H

#include "ITemperatureSensor.h"
#include <Arduino.h>
#include <Thermistor.h>

/**
 * @class ThermistorTemperatureSensor
 * @brief The ThermistorTemperatureSensor class represents a temperature sensor using a thermistor.
 * It implements the ITemperatureSensor interface and provides temperature measurement methods.
 */
class ThermistorTemperatureSensor : public ITemperatureSensor {
private:
    int thermistorPin; // Pin connected to the thermistor
    float temperatureCelsius;
    

public:
Thermistor* thermistor;
    /**
     * @brief Constructor.
     * @param pin The pin connected to the thermistor.
     */
    ThermistorTemperatureSensor(int pin)
      : thermistorPin(pin),
          temperatureCelsius(0.0),
          thermistor(new Thermistor(pin)){
        }

    ThermistorTemperatureSensor(Thermistor* thermistorPtr)
      : thermistorPin(-1),
          temperatureCelsius(0.0),
          thermistor(thermistorPtr){
        }

    // Implement ITemperatureSensor methods
    void update() override
    {
        temperatureCelsius = thermistor->readTemperature();
    }
    void initialize() override
    {
        
    }	
    float getTemperatureCelsius() override
    {
        return thermistor->readTemperature();
    }
    float getTemperatureFahrenheit() override
    {
        return thermistor->readTemperature(true);
    }


};

#endif // !THERMISTOR_TEMPERATURE_SENSOR_H
