#pragma once

#include <Arduino.h>    // Include the Arduino library
#include <ArduinoLog.h> // Include the ArduinoLog library
#include "cobold.hpp"
#include "Configuration.h"



class Host : public IHost
{
private:
    /* data */
    ServiceCollection *serviceCollection;
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
}

Host::~Host()
{
}

void Host::start()
{
    //get all the services that implement IHostedService
    auto hostedServices = serviceCollection->getServicesInheritingFromInterface<IHostedService*>();
    
    for (auto hostedService : hostedServices)
    {
        hostedService->start();
    }
}

void Host::stop()
{
    //get all the services that implement IHostedService
    auto hostedServices = serviceCollection->getServicesInheritingFromInterface<IHostedService*>();
    
    for (auto hostedService : hostedServices)
    {
        hostedService->stop();
    }
}       

ServiceCollection *Host::getServices()
{
    return serviceCollection;
}

