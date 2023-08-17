#ifndef IRELAY_H
#define IRELAY_H

#include "IActuator.h"

/**
 * @enum RelayState
 * Represents the possible states of a relay: OPENED or CLOSED.
 */
enum class RelayState {
    CLOSED, /**< The relay is CLOSED. */
    OPENED  /**< The relay is OPENED. */
};

/**
 * @class IRelay
 * @brief The IRelay interface defines a contract for interacting with relay devices.
 * It provides a common set of methods for controlling and querying the state of relay components.
 */
class IRelay : public abstractions::actuators::IActuator{
public:
    virtual ~IRelay() {}

    /**
     * @brief Close the relay, allowing current to flow through.
     * Implementing classes should define how to activate the relay circuitry.
     */
    virtual void close() = 0;

    /**
     * @brief Open the relay, stopping the flow of current.
     * Implementing classes should define how to deactivate the relay circuitry.
     */
    virtual void open() = 0;

    /**
     * @brief Toggle the relay, changing its state from OPENED to CLOSED or vice-versa.
     * Implementing classes should define how to toggle the relay circuitry.
     */
    virtual void toggle() = 0;

    /**
     * @brief Get the current state of the relay.
     * @return The current state of the relay (OPENED or CLOSED).
     */
    virtual RelayState getState() const = 0;

    /**
     * @brief Get the normal state of the relay.
     * @return The normal state of the relay (OPENED or CLOSED).
     */
    virtual RelayState getNormalState() const = 0;

    /**
     * @brief Check if the relay is currently in its normal state.
     * @return True if the relay is in its normal state, false otherwise.
     */
    virtual bool isNormalState() const = 0;
};

#endif // !IRELAY_H
