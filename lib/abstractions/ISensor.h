#pragma once

namespace abstractions
{
    namespace sensors
    {

        /**
         * @class ISensor
         * @brief The ISensor interface defines a contract for sensor devices.
         * It provides a common set of methods for updating and initializing sensor components.
         */
        class ISensor
        {
        public:
            /**
             * @brief Destructor.
             */
            virtual ~ISensor() {}

            /**
             * @brief Update the sensor data.
             * Implementing classes should define how to update sensor readings.
             */
            virtual void update() = 0;

            /**
             * @brief Initialize the sensor.
             * Implementing classes should define how to initialize the sensor.
             */
            virtual void initialize() = 0;
        };

    }
}