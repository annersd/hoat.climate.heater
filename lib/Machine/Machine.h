#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library
#include "cobold.hpp"

#include "HeatCircuit.h"                 // Include the HeatCircuit class
#include "Thermistor.h"                  // Include the Thermistor class
#include "ThermistorTemperatureSensor.h" // Include the ThermistorTemperatureSensor class
#include "ThreeWayValve.h"               // Include the ThreeWayValve class
#include "SingleRelay.h"                 // Include the SingleRelay class
#include "HeatCircuitOptions.h"          // Include the HeatCircuitComponentsOptions class
#include "Configuration.h"               // Include the Configuration class

#include <iostream>
#include <string>

class Machine : public cobold::components::IComponent, public cobold::hosting::IHostedService
{
private:
    Logging *logger;
    bool isRunning;

    HeatCircuit *hcFloor;
    HeatCircuit *hcHeater;
    cobold::sensors::ITemperatureSensor *hsOutside;

    HeatCircuitComponentsOptions optionsFloor;
    HeatCircuitComponentsOptions optionsHeater;

    cobold::time::ITimeline *timeline;

    HeatCircuit *constructHeatingCircuit(cobold::configuration::IConfiguration *section)
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

        cobold::actuators::IRelay *waterPump = new SingleRelay(options.getPumpRelayPin());

        return new HeatCircuit(ts, &threeWayValve, waterPump, options.getTargetTemperature());
    }

public:
    cobold::configuration::IConfiguration *Config = new Configuration();

    Machine(ServiceCollection *services) : isRunning(false)
    {
        // Constructor initialization
        logger = services->getService<Logging>();
    }

    void update() override
    {
        logger->noticeln("Updating machine...");
        // Update the machine's state or perform periodic tasks

        // timeline->update();

        // // Update the heating circuits
        // float tempOutside = hsOutside->getTemperatureCelsius();

        // hcFloor->setOutsideTemperatue(tempOutside);
        // hcFloor->update();

        // hcHeater->setOutsideTemperatue(tempOutside);
        // hcHeater->update();

        // vTaskDelay(1000 );
    }

    void initialize()
    {
        logger->noticeln("Initializing machine...");

        // Perform machine initialization tasks here
        timeline->initialize();

        // Get the section for heating.circuit.floor
        cobold::configuration::IConfiguration *floorSection = Config->getSection("heating.circuit.floor");
        hcFloor = constructHeatingCircuit(floorSection);
        delete floorSection;

        // Get the section for heating.circuit.heater
        cobold::configuration::IConfiguration *heaterSection = Config->getSection("heating.circuit.heater");
        hcHeater = constructHeatingCircuit(heaterSection);
        delete heaterSection;

        // Create outside temperature sensor
        int THERMISTOR_PIN_3 = atoi(Config->getValue("heating.circuit.outside.thermistor.pin").c_str());
        hsOutside = new ThermistorTemperatureSensor(
            new Thermistor(THERMISTOR_PIN_3, false, 10000, 10000, 30, 3950, 5));
    }

    void start() override
    {
        isRunning = true;

        // hcFloor->initialize();
        // hcHeater->initialize();
    }

    void stop() override
    {
        isRunning = false;
    }

    bool isMachineRunning() const
    {
        return isRunning;
    }
};
