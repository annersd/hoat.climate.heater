#ifndef ITIMELINE_H
#define ITIMELINE_H

#include <Arduino.h>
#include "IComponent.h"

class ITimeline : public IComponent
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

#endif // !ITIMELINE_H

