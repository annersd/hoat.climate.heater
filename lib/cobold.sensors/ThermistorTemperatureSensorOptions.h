#pragma once

#include <string>

class ThermistorTemperatureSensorOptions
{
private:
    /* data */
    int pin;
    std::string name;

public:
    ThermistorTemperatureSensorOptions(int pin) : pin(pin){

                                                  };
    ~ThermistorTemperatureSensorOptions() = default;

    int getPin() const
    {
        return pin;
    }

    void setPin(int pin)
    {
        this->pin = pin;
    }

    std::string getName() const
    {
        return name;
    }

    void setName(std::string name)
    {
        this->name = name;
    }
};
