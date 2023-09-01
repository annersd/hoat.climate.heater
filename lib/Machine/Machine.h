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
#include "ThreeWayValveOptions.h"        // Include the ThreeWayValveOptions class

#include "SoftwareTimeline.h"

#include <iostream>
#include <string>

class Machine : /*public cobold::components::IComponent, */public cobold::hosting::IHostedService
{
private:
    ServiceCollection *services;
    ILogger *logger;
    bool isRunning;

    HeatCircuit *hcFloor;
    HeatCircuit *hcHeater;
    cobold::sensors::ITemperatureSensor *hsOutside;

    HeatCircuitOptions optionsFloor;
    HeatCircuitOptions optionsHeater;

    cobold::time::ITimeline *timeline;

    HeatCircuit *constructHeatingCircuit(cobold::configuration::IConfiguration *section)
    {
        section->getSection("valve");

        auto valveOptions = ThreeWayValveOptions(
            atoi(section->getValue("hotRelayPin").c_str()),
            atoi(section->getValue("coldRelayPin").c_str()));

        HeatCircuitOptions options(
            atoi(section->getValue("thermistorPin").c_str()),
            atoi(section->getValue("pumpRelayPin").c_str()),
            atof(section->getValue("targetTemperature").c_str()),
            atof(section->getValue("maxSystemTemperature").c_str()),
            valveOptions);

        cobold::sensors::ThermistorTemperatureSensor *ts = new cobold::sensors::ThermistorTemperatureSensor(
            new Thermistor(options.getThermistorPin(), false, 10000, 10000, 30, 3950, 5));

        ThreeWayValve threeWayValve(services, options.getThreeWayValveOptions());

        cobold::actuators::IRelay *waterPump = new SingleRelay(services, options.getPumpRelayPin());

        return new HeatCircuit(ts, &threeWayValve, waterPump, options.getTargetTemperature(), options.getMaxSystemTemperature());
    }

public:
    cobold::configuration::IConfiguration *Config = new cobold::configuration::Configuration();

    Machine(ServiceCollection *services) : isRunning(false){
        // Constructor initialization
        this->services = services;
        logger = services->getService<ILogger>();
        logger->info("Machine::Machine()");
    }

    void update()  ///override
    {
        logger->info("Updating machine...");
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

    void initialize() //override
    {
        logger->info("Initializing machine...");

        // Perform machine initialization tasks here
        logger->info("Initializing timeline...");
        timeline = new SoftwareTimeline(0,0);
        timeline->initialize();

        // Get the section for heating.circuit.floor
        logger->info("Initializing floor heating circuit...");
        cobold::configuration::IConfiguration *floorSection = Config->getSection("heating.circuit.floor");
        hcFloor = constructHeatingCircuit(floorSection);
        delete floorSection;

        // Get the section for heating.circuit.heater
        logger->info("Initializing heater heating circuit...");
        cobold::configuration::IConfiguration *heaterSection = Config->getSection("heating.circuit.heater");
        hcHeater = constructHeatingCircuit(heaterSection);
        delete heaterSection;

        // Create outside temperature sensor
        logger->info("Initializing outside temperature sensor...");
        int THERMISTOR_PIN_3 = atoi(Config->getValue("heating.circuit.outside.thermistor.pin").c_str());
        hsOutside = new cobold::sensors::ThermistorTemperatureSensor(
            new Thermistor(THERMISTOR_PIN_3, false, 10000, 10000, 30, 3950, 5));
    }


    void start() override 
    {
        logger->info("Starting machine...");
        delay(1000);
        isRunning = true;
        
        initialize();

        hcFloor->initialize();
        hcHeater->initialize();
    }

    void stop() override
    {
        logger->info("Stopping machine...");
        isRunning = false;
    }

    bool isMachineRunning() const
    {
        return isRunning;
    }
};
