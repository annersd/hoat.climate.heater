#include "SingleRelay.h"

SingleRelay::SingleRelay() : pin(0), normalState(abstractions::actuators::RelayState::CLOSED), currentState(abstractions::actuators::RelayState::CLOSED) {}

SingleRelay::SingleRelay(int relayPin, abstractions::actuators::RelayState defaultNormalState)
    : pin(relayPin), normalState(defaultNormalState), currentState(defaultNormalState) {
    pinMode(pin, OUTPUT);
    setRelayState(currentState);
}

void SingleRelay::close() {
    setRelayState(abstractions::actuators::RelayState::CLOSED);
}

void SingleRelay::open() {
    setRelayState(abstractions::actuators::RelayState::OPENED);
}

void SingleRelay::toggle() {
    setRelayState(currentState == abstractions::actuators::RelayState::CLOSED ? abstractions::actuators::RelayState::OPENED : abstractions::actuators::RelayState::CLOSED);
}

abstractions::actuators::RelayState SingleRelay::getState() const {
    return currentState;
}

abstractions::actuators::RelayState SingleRelay::getNormalState() const {
    return normalState;
}

bool SingleRelay::isNormalState() const {
    return currentState == normalState;
}

void SingleRelay::update() {
    // Nothing to do here
}

void SingleRelay::initialize() {
    // Nothing to do here
}

void SingleRelay::setRelayState(abstractions::actuators::RelayState newState) {
    Log.infoln("Changing relay state on pin %d to %s", pin, (newState == abstractions::actuators::RelayState::CLOSED ? "CLOSED" : "OPENED"));
    digitalWrite(pin, newState == normalState ? HIGH : LOW);
    currentState = newState;
}
