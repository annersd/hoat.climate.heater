#pragma once

#include "IComponent.h"

namespace abstractions
{
    namespace time
    {

        class ITimeline : public abstractions::components::IComponent
        {

        public:
            void update() override
            {
            }

            void initialize() override
            {
            }

            virtual unsigned long long now() = 0;
        };

    }
}