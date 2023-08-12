#ifndef SINGLE_RELAY_H
#define SINGLE_RELAY_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include "IRelay.h"

class SingleRelay : public IRelay {
private:
    int pin;
    RelayState normalState;
    RelayState currentState;

public:
    SingleRelay() : pin(0), normalState(RelayState::CLOSED), currentState(RelayState::CLOSED) {}

    SingleRelay(int relayPin, RelayState defaultNormalState = RelayState::CLOSED)
        : pin(relayPin), normalState(defaultNormalState), currentState(defaultNormalState) {
        pinMode(pin, OUTPUT);
        setRelayState(currentState);
    }

    void close() override {
        setRelayState(RelayState::CLOSED);
    }

    void open() override {
        setRelayState(RelayState::OPENED);
    }

    void toggle() override {
        setRelayState(currentState == RelayState::CLOSED ? RelayState::OPENED : RelayState::CLOSED);
    }

    RelayState getState() const override {
        return currentState;
    }

    RelayState getNormalState() const override {
        return normalState;
    }

    bool isNormalState() const override {
        return currentState == normalState;
    }

    void update() override {
        // Nothing to do here
    }

    void initialize() override {
        // Nothing to do here
    }

private:
    void setRelayState(RelayState newState) {
        Log.infoln("Changing relay state on pin %d to %s", pin, (newState == RelayState::CLOSED ? "CLOSED" : "OPENED"));
        digitalWrite(pin, newState == normalState ? HIGH : LOW);
        currentState = newState;
    }
};

#endif // !SINGLE_RELAY_H
