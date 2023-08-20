#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library
#include "abstractions.hpp"

#include "HeatCircuit.h"                 // Include the HeatCircuit class
#include "Thermistor.h"                  // Include the Thermistor class
#include "ThermistorTemperatureSensor.h" // Include the ThermistorTemperatureSensor class
#include "ThreeWayValve.h"               // Include the ThreeWayValve class
#include "SingleRelay.h"                 // Include the SingleRelay class
#include "HeatCircuitOptions.h"          // Include the HeatCircuitComponentsOptions class
#include "Configuration.h"               // Include the Configuration class

#include <iostream>
#include <string>

class Machine : public abstractions::components::IComponent
{
private:
    Logging *logger;
    bool isRunning;

    HeatCircuit *hcFloor;
    HeatCircuit *hcHeater;
    abstractions::sensors::ITemperatureSensor *hsOutside;

    HeatCircuitComponentsOptions optionsFloor;
    HeatCircuitComponentsOptions optionsHeater;

    abstractions::time::ITimeline *timeline;

    HeatCircuit *constructHeatingCircuit(abstractions::configuration::IConfiguration *section)
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

        abstractions::actuators::IRelay *waterPump = new SingleRelay(options.getPumpRelayPin());

        return new HeatCircuit(ts, &threeWayValve, waterPump, options.getTargetTemperature());
    }

public:
    abstractions::configuration::IConfiguration *Config = new Configuration();

    Machine(ServiceCollection *services) : isRunning(false)
    {
        // Constructor initialization
        logger = services->getService<Logging>();
    }

    void update() override
    {
        logger->noticeln("Updating machine...");
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
        logger->noticeln("Initializing machine...");

        // Perform machine initialization tasks here
        timeline->initialize();

        // Get the section for heating.circuit.floor
        abstractions::configuration::IConfiguration *floorSection = Config->getSection("heating.circuit.floor");
        hcFloor = constructHeatingCircuit(floorSection);
        delete floorSection;

        // Get the section for heating.circuit.heater
        abstractions::configuration::IConfiguration *heaterSection = Config->getSection("heating.circuit.heater");
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
};
