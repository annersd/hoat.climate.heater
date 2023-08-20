
#pragma once

#include "IComponent.h"

namespace abstractions
{

    namespace actuators
    {
        /**
         * @class IActuator
         * @brief The IActuator interface defines a contract for interacting with actuator devices.
         *        It provides a common set of methods for controlling and querying the state of actuator components.
         */
        class IActuator : public abstractions::components::IComponent
        {
        public:
            virtual ~IActuator() {}

            /**
             * @brief Update the state or behavior of the actuator.
             *        This method should be called periodically to ensure proper operation of the actuator.
             */
            virtual void update() = 0;

            /**
             * @brief Initialize the actuator.
             *        This method should be called during system initialization to prepare the actuator for operation.
             */
            virtual void initialize() = 0;
        };

    } // namespace acts

} // namespace name
