#pragma once

#include "cobold.hpp"

/**
 * @brief Interface for a hosted service that can be started and stopped.
 */
class IHostedService
{
public:
    /**
     * @brief Start the hosted service.
     */
    virtual void start() = 0;

    /**
     * @brief Stop the hosted service.
     */
    virtual void stop() = 0;
};
