#ifndef SOFTWARECLOCK_H
#define SOFTWARECLOCK_H

#include <Arduino.h>


/// @brief Implements a software clock that can be adjusted to match the current time.
class SoftwareClock {
private:
  unsigned long startTime;
  unsigned long offset;

public:
  SoftwareClock() {
    startTime = millis();
    offset = 0;
  }

  void reset() {
    startTime = millis();
  }

  void adjustOffset(unsigned long newOffset) {
    offset = newOffset;
  }

  unsigned long elapsed() {
    return millis() + offset - startTime;
  }
};

#endif // !SOFTWARECLOCK_H