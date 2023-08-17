#ifndef MACHINE_H
#define MACHINE_H


#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library

#include "IComponent.h"                  // Include the IComponent interface
#include "HeatCircuit.h"                 // Include the HeatCircuit class
#include "Thermistor.h"                  // Include the Thermistor class
#include "ThermistorTemperatureSensor.h" // Include the ThermistorTemperatureSensor class
#include "ThreeWayValve.h"               // Include the ThreeWayValve class
#include "ITemperatureSensor.h"          // Include the ITemperatureSensor interface
#include "SingleRelay.h"                 // Include the SingleRelay class
#include "HeatCircuitOptions.h"          // Include the HeatCircuitComponentsOptions class
#include "ITimeLine.h"                   // Include the ITimeLine interface
#include "IConfiguration.h"              // Include the IConfiguration interface
#include "Configuration.h"               // Include the Configuration class

#include <iostream>
#include <string>

class Machine : public IComponent
{
private:
    bool isRunning;

    HeatCircuit *hcFloor;
    HeatCircuit *hcHeater;
    ITemperatureSensor *hsOutside;

    HeatCircuitComponentsOptions optionsFloor;
    HeatCircuitComponentsOptions optionsHeater;

    ITimeline *timeline;

    HeatCircuit *constructHeatingCircuit(IConfiguration *section)
    {
        HeatCircuitComponentsOptions options(
            atoi(section->getValue("thermistorPin").c_str()),
            atoi(section->getValue("hotRelayPin").c_str()),
            atoi(section->getValue("coldRelayPin").c_str()),
            atoi(section->getValue("pumpRelayPin").c_str()),
            atof(section->getValue("targetTemperature").c_str()));

        ThermistorTemperatureSensor *ts = new ThermistorTemperatureSensor(
            new Thermistor(options.getThermistorPin(), false, 10000, 10000, 30, 3950, 5));

        ThreeWayValve threeWayValve(
            new SingleRelay(options.getHotRelayPin()),
            new SingleRelay(options.getColdRelayPin()));

        IRelay *waterPump = new SingleRelay(options.getPumpRelayPin());

        return new HeatCircuit(ts, &threeWayValve, waterPump, options.getTargetTemperature());
    }

public:
    Machine() : isRunning(false)
    {
        // Constructor initialization
    }

    void update() override
    {
        // Update the machine's state or perform periodic tasks

        timeline->update();

        // Update the heating circuits
        float tempOutside = hsOutside->getTemperatureCelsius();

        hcFloor->setOutsideTemperatue(tempOutside);
        hcFloor->update();

        hcHeater->setOutsideTemperatue(tempOutside);
        hcHeater->update();

        // vTaskDelay(1000 );
    }

    void initialize()
    {
        // Perform machine initialization tasks here
        timeline->initialize();

        // Get the section for heating.circuit.floor
        IConfiguration *floorSection = Config->getSection("heating.circuit.floor");
        hcFloor = constructHeatingCircuit(floorSection);
        delete floorSection;

        // Get the section for heating.circuit.heater
        IConfiguration *heaterSection = Config->getSection("heating.circuit.heater");
        hcHeater = constructHeatingCircuit(heaterSection);
        delete heaterSection;

        // Create outside temperature sensor
        int THERMISTOR_PIN_3 = atoi(Config->getValue("heating.circuit.outside.thermistor.pin").c_str());
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

    IConfiguration *Config = new Configuration();
};

#endif // MACHINE_H
