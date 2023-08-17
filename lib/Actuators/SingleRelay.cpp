#include "SingleRelay.h"

SingleRelay::SingleRelay() : pin(0), normalState(RelayState::CLOSED), currentState(RelayState::CLOSED) {}

SingleRelay::SingleRelay(int relayPin, RelayState defaultNormalState)
    : pin(relayPin), normalState(defaultNormalState), currentState(defaultNormalState) {
    pinMode(pin, OUTPUT);
    setRelayState(currentState);
}

void SingleRelay::close() {
    setRelayState(RelayState::CLOSED);
}

void SingleRelay::open() {
    setRelayState(RelayState::OPENED);
}

void SingleRelay::toggle() {
    setRelayState(currentState == RelayState::CLOSED ? RelayState::OPENED : RelayState::CLOSED);
}

RelayState SingleRelay::getState() const {
    return currentState;
}

RelayState SingleRelay::getNormalState() const {
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

void SingleRelay::setRelayState(RelayState newState) {
    Log.infoln("Changing relay state on pin %d to %s", pin, (newState == RelayState::CLOSED ? "CLOSED" : "OPENED"));
    digitalWrite(pin, newState == normalState ? HIGH : LOW);
    currentState = newState;
}
