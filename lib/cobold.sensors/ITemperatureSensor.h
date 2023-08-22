#pragma once

#include "ISensor.h"

namespace cobold
{
    namespace sensors
    {

        /**
         * @class ITemperatureSensor
         * @brief The ITemperatureSensor interface defines a contract for temperature sensor devices.
         * It extends the ISensor interface and provides methods for temperature measurement.
         */
        class ITemperatureSensor : public ISensor
        {
        public:
            /**
             * @brief Destructor.
             */
            virtual ~ITemperatureSensor() {}

            /**
             * @brief Update the temperature reading.
             * Implementing classes should define how to update the temperature measurement.
             */
            virtual void update() override = 0;

            /**
             * @brief Initialize the temperature sensor.
             * Implementing classes should define how to initialize the sensor.
             */
            virtual void initialize() override = 0;

            /**
             * @brief Get the current temperature in degrees Celsius.
             * Implementing classes should provide the actual temperature value.
             * @return The current temperature reading in degrees Celsius.
             */
            virtual float getTemperatureCelsius() = 0;

            /**
             * @brief Get the current temperature in degrees Fahrenheit.
             * Implementing classes should provide the actual temperature value.
             * @return The current temperature reading in degrees Fahrenheit.
             */
            virtual float getTemperatureFahrenheit() = 0;
        };

    }
}