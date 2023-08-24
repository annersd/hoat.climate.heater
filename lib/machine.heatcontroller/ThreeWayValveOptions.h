#pragma once

class ThreeWayValveOptions {
private:
    int hotPin;
    int coldPin;
public:
    ThreeWayValveOptions(int hotPin, int coldPin)
        : hotPin(hotPin),
          coldPin(coldPin) {
    }

    ThreeWayValveOptions() {
        hotPin = -1;
        coldPin = -1;
    }

    int getHotPin() const {
        return hotPin;
    }

    void setHotPin(int pin) {
        hotPin = pin;
    }

    int getColdPin() const {
        return coldPin;
    }

    void setColdPin(int pin) {
        coldPin = pin;
    }
};