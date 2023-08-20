#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library
#include "abstractions.hpp"
#include "Configuration.h"

class Host
{
private:
    ServiceCollection *serviceCollection;
    abstractions::configuration::IConfiguration *configuration;
    std::vector<std::function<void(abstractions::configuration::IConfiguration *)>> configurationLambdas;
    std::vector<std::function<void(ServiceCollection *)>> serviceConfigurationLambdas;

public:
    Host(/* args */);
    ~Host();
    void run();
    void build();
    void configureAppConfiguration(std::function<void(abstractions::configuration::IConfiguration *)> configLambda);
    void configureServices(std::function<void(ServiceCollection *)> serviceConfigLambda);
};

Host::Host(/* args */)
{
    serviceCollection = new ServiceCollection();
    configuration = new Configuration();
}

Host::~Host()
{
    delete configuration;
    delete serviceCollection;
}

void Host::build()
{
    Serial.begin(115200);

    serviceCollection->addServiceWithConstructor<Logging>([](ServiceCollection *services) -> void *
                                                          { 
        // Initialize with log level and log output.
        Log.begin(LOG_LEVEL_VERBOSE, &Serial);
        return &Log; });

    serviceCollection->addService<abstractions::configuration::IConfiguration>(configuration);

    serviceCollection->addService<MessageBus>();

    for (auto configLambda : configurationLambdas)
    {
        configLambda(configuration);
    }

    for (auto serviceConfigLambda : serviceConfigurationLambdas)
    {
        serviceConfigLambda(serviceCollection);
    }

    Logging *logger = serviceCollection->getService<Logging>();
    logger->infoln("Starting up...");
}

void Host::configureAppConfiguration(std::function<void(abstractions::configuration::IConfiguration *)> configLambda)
{
    configurationLambdas.push_back(configLambda);
}

void Host::run()
{
    Logging *logger = serviceCollection->getService<Logging>();
    logger->infoln("Running...");
    Machine *machine = serviceCollection->getService<Machine>();
    machine->initialize();
    while (true)
    {
        // machine->run();
    }
}

void Host::configureServices(std::function<void(ServiceCollection *)> serviceConfigLambda)
{
    serviceConfigurationLambdas.push_back(serviceConfigLambda);
}