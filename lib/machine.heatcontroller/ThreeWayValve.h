#pragma once

#include <Arduino.h>
#include <cobold.hpp>
#include "SingleRelay.h"
#include "ThreeWayValveOptions.h"

/**
 * @brief Enumeration representing the movement direction of the valve.
 */
enum class ValveMovementDirection
{
    None,   ///< Valve is not moving
    ToCold, ///< Valve is moving to the cold position
    ToHot   ///< Valve is moving to the hot position
};

/**
 * @brief Controls a three-way valve
 */
class ThreeWayValve
{
private:
    // The relays used to control the valve
    cobold::actuators::IRelay *moveToHotRelay;
    cobold::actuators::IRelay *moveToColdRelay;

    // The service collection and references to the services used by the valve 
    ServiceCollection *services;
    ILogger *logger;
    ThreeWayValveOptions *options;
    cobold::time::ITimeline *timeLine;

    // The state of the valve
    bool isMoving;
    ValveMovementDirection movementDirection;
    unsigned long long startTime;
    float movementDuration;

public:
    ThreeWayValve(ServiceCollection *services, ThreeWayValveOptions options);
    ~ThreeWayValve();
    void update();
    /**
     * @brief Moves the valve to the cold position
     * @param duration The duration of the movement in seconds
     *
     * @details
     * This method moves the valve to the cold position for the specified duration.
     * The duration is specified in seconds.
     * The valve will stop moving after the specified duration.
     */
    void moveToCold(float duration);

    /**
     * @brief Moves the valve to the hot position
     * @param duration The duration of the movement in seconds
     *
     * @details
     * This method moves the valve to the hot position for the specified duration.
     * The duration is specified in seconds.
     * The valve will stop moving after the specified duration.
     */
    void moveToHot(float duration);

    /**
     * @brief Stops the valve movement
     */
    void stopMoving()
    {
        logger->info("Stopping valve movement");
        moveToColdRelay->close();
        moveToHotRelay->close();

        isMoving = false;
        movementDirection = ValveMovementDirection::None;
        movementDuration = 0.0;
    }

    /**
     * @brief Returns true if the valve is currently moving
     */
    bool getIsMoving()
    {
        return isMoving;
    }

    /**
     * @brief Returns the current movement direction of the valve
     */
    ValveMovementDirection getMovementDirection()
    {
        return movementDirection;
    }
};

ThreeWayValve::ThreeWayValve(ServiceCollection *services, ThreeWayValveOptions options)
{
    // Store the references to the services
    this->services = services;
    this->logger = services->getService<ILogger>();
    this->options = &options;

    // Initialize the relays
    this->moveToHotRelay = new SingleRelay(services, options.getHotPin());
    this->moveToColdRelay = new SingleRelay(services, options.getColdPin());

    // Initialize the state of the valve
    isMoving = false;
    movementDirection = ValveMovementDirection::None;
    movementDuration = 0.0;
    timeLine = services->getService<cobold::time::ITimeline>();
}

ThreeWayValve::~ThreeWayValve()
{
    delete moveToHotRelay;
    delete moveToColdRelay;
}

void ThreeWayValve::update()
{
    logger->info("Updating three-way valve");
}

void ThreeWayValve::moveToCold(float duration)
{
    // stop the valve even if it is not moving
    // this is to ensure the valve is in a known state
    stopMoving();

    logger->info("Starting to move to cold for $s seconds", String(duration));
    isMoving = true;
    movementDirection = ValveMovementDirection::ToCold;
    movementDuration = duration;
    startTime = timeLine->now();
    moveToColdRelay->open();
}

void ThreeWayValve::moveToHot(float duration)
{
    // stop the valve even if it is not moving
    // this is to ensure the valve is in a known state
    stopMoving();

    logger->info("Starting to move to hot for $s seconds", String(duration));
    isMoving = true;
    movementDirection = ValveMovementDirection::ToHot;
    movementDuration = duration;
    startTime = timeLine->now();
    moveToHotRelay->open();
}
