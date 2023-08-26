#pragma once

/**
 * @brief Options for a three-way valve
 * 
 * @details
 * This class is used to configure a three-way valve.
*/
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