#pragma once

#include <Arduino.h>
#include <Cobold.hpp>
#include <Thermistor.h>
#include <ThermistorTemperatureSensorOptions.h>

namespace cobold
{
    namespace sensors
    {

        /**
         * @class ThermistorTemperatureSensor
         * @brief The ThermistorTemperatureSensor class represents a temperature sensor using a thermistor.
         * It implements the ITemperatureSensor interface and provides temperature measurement methods.
         */
        class ThermistorTemperatureSensor : public cobold::sensors::ITemperatureSensor
        {
        private:
            int thermistorPin; // Pin connected to the thermistor
            float temperatureCelsius;

        public:
            Thermistor *thermistor;
            /**
             * @brief Constructor.
             * @param pin The pin connected to the thermistor.
             */
            ThermistorTemperatureSensor(ThermistorTemperatureSensorOptions *options)
                : thermistorPin(options->getPin()),
                  temperatureCelsius(0.0),
                  thermistor(new Thermistor(options->getPin()))
            {
            }

            ThermistorTemperatureSensor(Thermistor *thermistorPtr)
                : thermistorPin(-1),
                  temperatureCelsius(0.0),
                  thermistor(thermistorPtr)
            {
            }

            // Implement ITemperatureSensor methods
            void update() override
            {
                temperatureCelsius = thermistor->readTemperature();
            }
            void initialize() override
            {

            }

            float getTemperatureCelsius() override
            {
                return thermistor->readTemperature();
            }
            float getTemperatureFahrenheit() override
            {
                return thermistor->readTemperature(true);
            }
        };

    } // namespace sensors

} // namespace cobold
