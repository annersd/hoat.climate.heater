#ifndef IACTUATOR_H
#define IACTUATOR_H

/**
 * @class IActuator
 * @brief The IActuator interface defines a contract for interacting with actuator devices.
 * It provides a common set of methods for controlling and querying the state of actuator components.
 */
class IActuator {
public:
    virtual ~IActuator() {}

    virtual void update() = 0;

    virtual void initialize() = 0;
};

#endif // !IACTUATOR_H
