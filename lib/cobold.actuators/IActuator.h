
#pragma once

#include "IComponent.h"

namespace cobold
{

    namespace actuators
    {
        /**
         * @class IActuator
         * @brief The IActuator interface defines a contract for interacting with actuator devices.
         *        It provides a common set of methods for controlling and querying the state of actuator components.
         */
        class IActuator : public cobold::components::IComponent
        {
        public:
            ~IActuator() override = default;

            /**
             * @brief Update the state or behavior of the actuator.
             *        This method should be called periodically to ensure proper operation of the actuator.
             */
            void update() override = 0;

            /**
             * @brief Initialize the actuator.
             *        This method should be called during system initialization to prepare the actuator for operation.
             */
            void initialize() override = 0;
        };

    } // namespace actuators

} // namespace cobold
