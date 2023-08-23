#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library
#include "cobold.hpp"
#include "Configuration.h"

namespace cobold
{
    namespace hosting
    {

        class Host : public IHost
        {
        private:
            /* data */
            ServiceCollection *serviceCollection;
            Logging *logger;

        public:
            explicit Host(ServiceCollection *serviceCollection);
            ~Host();
            void start() override;
            void stop() override;
            ServiceCollection *getServices();
        };

        Host::Host(ServiceCollection *serviceCollection)
        {
            this->serviceCollection = serviceCollection;
            logger = serviceCollection->getService<Logging>();
        }

        Host::~Host()
        {
        }

        void Host::start()
        {
            logger->verboseln("Host::start()");
            // get all the services that implement IHostedService
            auto hostedServices = serviceCollection->getServicesInheritingFromInterface();

            for (auto hostedService : hostedServices)
            {
                logger->verboseln("Host::start() - starting hosted service");
                hostedService->start();
            }
            logger->verboseln("Host::start() - done");
        }

        void Host::stop()
        {
            // get all the services that implement IHostedService
            auto hostedServices = serviceCollection->getServicesInheritingFromInterface();

            for (auto hostedService : hostedServices)
            {
                hostedService->stop();
            }
        }

        ServiceCollection *Host::getServices()
        {
            return serviceCollection;
        }

    } // namespace hosting
} // namespace cobold