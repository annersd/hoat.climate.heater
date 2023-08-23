#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library

#include "cobold.hpp"
#include "Configuration.h"
#include "IHostBuilder.h"
#include "Host.h"

namespace cobold
{
    namespace hosting
    {

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
            Serial.begin(115200);
            // Initialize with log level and log output.
            Log.begin(LOG_LEVEL_VERBOSE, &Serial);

            serviceCollection = new ServiceCollection(&Log);
            configuration = new cobold::configuration::Configuration();
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

            serviceCollection->addService<Logging>([](ServiceCollection *services) -> void *
                                                   { return &Log; });

            Log.verbose("HostBuilder::build() - Building Services Collection...");

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
            logger->verboseln("HostBuilder::build() - Services Collection built...");

            logger->verboseln("HostBuilder::build() - Creating Host...");
            auto host = new Host(serviceCollection);
            logger->verboseln("HostBuilder::build() - Host created...");

            return host;
        }

    }
}