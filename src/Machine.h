#ifndef MACHINE_H
#define MACHINE_H

#include <Arduino.h>                     // Include the Arduino library
#include "IComponent.h"                  // Include the IComponent interface
#include "HeatCircuit.h"                 // Include the HeatCircuit class
#include "Thermistor.h"                  // Include the Thermistor class
#include "ThermistorTemperatureSensor.h" // Include the ThermistorTemperatureSensor class
#include "ThreeWayValve.h"               // Include the ThreeWayValve class
#include "ITemperatureSensor.h"          // Include the ITemperatureSensor interface
#include "SingleRelay.h"                 // Include the SingleRelay class
#include "HeatCircuitOptions.h"          // Include the HeatCircuitComponentsOptions class

class Machine : public IComponent
{
private:
    bool isRunning;

    HeatCircuit *hcFloor;
    HeatCircuit *hcHeater;
    ITemperatureSensor *hsOutside;

    HeatCircuitComponentsOptions optionsFloor;
    HeatCircuitComponentsOptions optionsHeater;

    HeatCircuit *constructHeatingCircuit(HeatCircuitComponentsOptions &options)
    {
        ThermistorTemperatureSensor *ts = new ThermistorTemperatureSensor(
            new Thermistor(options.getThermistorPin(), false, 10000, 10000, 30, 3950, 5));

        ThreeWayValve threeWayValve(
            new SingleRelay(options.getHotRelayPin()),
            new SingleRelay(options.getColdRelayPin()));

        IRelay *waterPump = new SingleRelay(options.getPumpRelayPin());

        return new HeatCircuit(ts, &threeWayValve, waterPump, options.getTargetTemperature());
    }

public:
    Machine() : isRunning(false),
            optionsFloor(0, 5, 6, 3, 21.0),  // Initialize options for floor
            optionsHeater(1, 5, 6, 4, 21.0)  // Initialize options for heater
    {
        // Constructor initialization


    }

    void update() override
    {
        // Update the machine's state or perform periodic tasks

        // Update the heating circuits
        float tempOutside = hsOutside->getTemperatureCelsius();

        hcFloor->setOutsideTemperatue(tempOutside);
        hcFloor->update();

        hcHeater->setOutsideTemperatue(tempOutside);
        hcHeater->update();
    }

    void initialize()
    {
        // Perform machine initialization tasks here

        hcFloor = constructHeatingCircuit(optionsFloor);
        hcHeater = constructHeatingCircuit(optionsHeater);

        // Create outside temperature sensor
        int THERMISTOR_PIN_3 = 2;
        hsOutside = new ThermistorTemperatureSensor(
            new Thermistor(THERMISTOR_PIN_3, false, 10000, 10000, 30, 3950, 5));
    }

    void start()
    {
        isRunning = true;

        hcFloor->initialize();
        hcHeater->initialize();
    }

    void stop()
    {
        isRunning = false;
    }

    bool isMachineRunning() const
    {
        return isRunning;
    }
};

#endif // MACHINE_H
