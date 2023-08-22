#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library
#include "cobold.hpp"
#include "Configuration.h"
#include "IHostBuilder.h"
#include "Host.h"

class HostBuilder : public IHostBuilder
{
private:
    ServiceCollection *serviceCollection;
    cobold::configuration::IConfiguration *configuration;
    std::vector<std::function<void(cobold::configuration::IConfiguration *)>> configurationLambdas;
    std::vector<std::function<void(ServiceCollection *)>> serviceConfigurationLambdas;

public:
    HostBuilder(/* args */);
    ~HostBuilder();
    IHostBuilder *configureAppConfiguration(std::function<void(cobold::configuration::IConfiguration *)> configLambda);
    IHostBuilder *configureServices(std::function<void(ServiceCollection *)> serviceConfigLambda);
    IHost *build();
};

HostBuilder::HostBuilder(/* args */)
{
    serviceCollection = new ServiceCollection();
    configuration = new Configuration();
}

HostBuilder::~HostBuilder()
{
    delete configuration;
    delete serviceCollection;
}

IHostBuilder *HostBuilder::configureAppConfiguration(std::function<void(cobold::configuration::IConfiguration *)> configLambda)
{
    configurationLambdas.push_back(configLambda);
    return this;
}

IHostBuilder *HostBuilder::configureServices(std::function<void(ServiceCollection *)> serviceConfigLambda)
{
    serviceConfigurationLambdas.push_back(serviceConfigLambda);
    return this;
}



IHost *HostBuilder::build()
{
    Serial.begin(115200);

    serviceCollection->addService<Logging>([](ServiceCollection *services) -> void * {
        // Initialize with log level and log output.
        Log.begin(LOG_LEVEL_VERBOSE, &Serial);
        return &Log;
    });

    serviceCollection->addService<cobold::configuration::IConfiguration>(configuration);

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

    return new Host(serviceCollection);
}