#pragma once

#include <abstractions.hpp>

class MillisTimeline : public abstractions::time::ITimeline
{
private:
    unsigned long long initialMillis;
    unsigned long long cachedMillis;

public:
    MillisTimeline(unsigned long long initialSeconds = 0)
        : initialMillis(millis() - (initialSeconds * 1000)), cachedMillis(0)
    {
    }

    void update() override
    {
        // No need to update for MillisTimeline
    }

    unsigned long long now() override
    {
        cachedMillis = millis() - initialMillis;
        return cachedMillis;
    }

    void adjust(unsigned long long newInitialMillis)
    {
        initialMillis = newInitialMillis;
    }
};

#endif // MILLISTIMELINE_H
