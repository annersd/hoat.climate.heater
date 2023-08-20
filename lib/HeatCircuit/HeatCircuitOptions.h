#pragma once

class HeatCircuitComponentsOptions {
public:
    HeatCircuitComponentsOptions(int thermistorPin, int hotRelayPin, int coldRelayPin, int pumpRelayPin, int targetTemperature )
        : thermistorPin(thermistorPin),
          hotRelayPin(hotRelayPin),
          coldRelayPin(coldRelayPin),
          pumpRelayPin(pumpRelayPin),
          targetTemperature(targetTemperature) {
    }

    HeatCircuitComponentsOptions() {
        thermistorPin = -1;
        hotRelayPin = -1;
        coldRelayPin = -1;
        pumpRelayPin = -1;
        targetTemperature = 0.0;
        
    }

    int getThermistorPin() const {
        return thermistorPin;
    }

    void setThermistorPin(int pin) {
        thermistorPin = pin;
    }

    int getHotRelayPin() const {
        return hotRelayPin;
    }

    void setHotRelayPin(int pin) {
        hotRelayPin = pin;
    }

    int getColdRelayPin() const {
        return coldRelayPin;
    }

    void setColdRelayPin(int pin) {
        coldRelayPin = pin;
    }

    int getPumpRelayPin() const {
        return pumpRelayPin;
    }

    void setPumpRelayPin(int pin) {
        pumpRelayPin = pin;
    }

    void setTargetTemperature(float temp) {
        targetTemperature = temp;
    }

    float getTargetTemperature() const {
        return targetTemperature;
    }

private:
    int thermistorPin;
    int hotRelayPin;
    int coldRelayPin;
    int pumpRelayPin;
    float targetTemperature;
};