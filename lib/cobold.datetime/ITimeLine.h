#pragma once

#include "../cobold.components/IComponent.h"

namespace cobold {
    namespace time {

        class ITimeline : public cobold::components::IComponent {

        public:
            void update() override {
            }

            void initialize() override {
            }

            virtual unsigned long long now() = 0;
        };

    }
}