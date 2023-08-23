#include "SingleRelay.h"

SingleRelay::SingleRelay(ServiceCollection *services, int relayPin, cobold::actuators::RelayState defaultNormalState)
    : pin(relayPin), normalState(defaultNormalState), currentState(defaultNormalState)
{
    this->services = services;
    logger = services->getService<Logging>();

    // Initialize the relay
    initialize();
}

void SingleRelay::close()
{
    setRelayState(cobold::actuators::RelayState::CLOSED);
}

void SingleRelay::open()
{
    setRelayState(cobold::actuators::RelayState::OPENED);
}

void SingleRelay::toggle()
{
    setRelayState(currentState == cobold::actuators::RelayState::CLOSED ? cobold::actuators::RelayState::OPENED : cobold::actuators::RelayState::CLOSED);
}

cobold::actuators::RelayState SingleRelay::getState() const
{
    return currentState;
}

cobold::actuators::RelayState SingleRelay::getNormalState() const
{
    return normalState;
}

bool SingleRelay::isNormalState() const
{
    return currentState == normalState;
}

void SingleRelay::update()
{
    // Nothing to do here
}

void SingleRelay::initialize()
{
    pinMode(pin, OUTPUT);
    setRelayState(currentState);
}

void SingleRelay::setRelayState(cobold::actuators::RelayState newState)
{
    logger->infoln("Changing relay state on pin %d to %s", pin, (newState == cobold::actuators::RelayState::CLOSED ? "CLOSED" : "OPENED"));
    digitalWrite(pin, newState == normalState ? HIGH : LOW);
    currentState = newState;
}
