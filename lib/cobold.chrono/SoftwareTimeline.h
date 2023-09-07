#pragma once

#include <Cobold.hpp>
#include <stdint.h>

/**
 * @brief Implementation of ITimeline using the Arduino micros() function.
 *
 * This class provides a timeline based on the micros() function from the Arduino framework.
 * It allows you to measure elapsed time in microseconds.
 */
class SoftwareTimeline : public cobold::time::ITimeline
{
private:
    cobold::time::timeline_t offset;        /**< The initial time offset in microseconds. */
    uint64_t initialMicros; /**< The initial value of micros(). */

public:
    /**
     * @brief Constructor for MicrosTimeline.
     *
     * Initializes the MicrosTimeline with an optional initial time offset in microseconds.
     *
     * @param offset The initial time offset in microseconds (default is 0).
     * @param initialMicros The initial time offset in microseconds (default is 0).
     */
    SoftwareTimeline(cobold::time::timeline_t offset, uint64_t initialMicros)
        : offset(offset),
          initialMicros(initialMicros)
    {
        if (initialMicros == 0)
        {
            adjust(micros());
        }
    }

    /**
     * @brief Update method for the timeline.
     *
     * MicrosTimeline does not require periodic updates, so this method does nothing.
     */
    void update() override
    {
        // No need to update for MicrosTimeline
    }

    /**
     * @brief Get the current time in microseconds.
     *
     * @return The current time in microseconds since the timeline started.
     */
    cobold::time::timeline_t now() override
    {
        return millis() * 1000; 
        // return micros() ;
        // return micros() - initialMicros + offset;
    }

    /**
     * @brief Adjust the initial time offset.
     *
     * This method allows you to adjust the initial time offset of the timeline.
     *
     * @param newInitialMicros The new initial time offset in microseconds.
     */
    void adjust(uint64_t newInitialMicros)
    {
        initialMicros = newInitialMicros;
    }
};
