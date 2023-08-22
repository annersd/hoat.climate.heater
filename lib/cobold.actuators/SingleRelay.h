#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <cobold.hpp>

/**
 * @class SingleRelay
 * @brief Represents a single relay device.
 *        This class implements the IRelay interface and provides methods for controlling and querying the state of the relay.
 */
class SingleRelay : public cobold::actuators::IRelay {
private:
    int pin;                 ///< The pin number connected to the relay.
    cobold::actuators::RelayState normalState;  ///< The normal state (open or closed) of the relay.
    cobold::actuators::RelayState currentState; ///< The current state (open or closed) of the relay.

public:
    /**
     * @brief Default constructor.
     *        Creates a SingleRelay object with default values.
     */
    SingleRelay();

    /**
     * @brief Constructor with pin and default normal state.
     * @param relayPin The pin number connected to the relay.
     * @param defaultNormalState The default normal state of the relay (open or closed).
     */
    SingleRelay(int relayPin, cobold::actuators::RelayState defaultNormalState = cobold::actuators::RelayState::CLOSED);

    // Methods to control the relay

    /**
     * @brief Close the relay (set to the normal state).
     *        This method closes the relay and sets it to its normal state.
     */
    void close() override;

    /**
     * @brief Open the relay (opposite of the normal state).
     *        This method opens the relay, which is the opposite of its normal state.
     */
    void open() override;

    /**
     * @brief Toggle the relay state.
     *        This method toggles the relay state between open and closed.
     */
    void toggle() override;

    // Methods to query the relay state

    /**
     * @brief Get the current state of the relay.
     * @return The current state of the relay (open or closed).
     */
    cobold::actuators::RelayState getState() const override;

    /**
     * @brief Get the normal state of the relay.
     * @return The normal state of the relay (open or closed).
     */
    cobold::actuators::RelayState getNormalState() const override;

    /**
     * @brief Check if the relay is in its normal state.
     * @return True if the relay is in its normal state, false otherwise.
     */
    bool isNormalState() const override;

    // Update and initialize methods (override from IRelay)

    /**
     * @brief Update the relay state (no action needed).
     *        This method is called periodically to update the relay state.
     */
    void update() override;

    /**
     * @brief Initialize the relay (no action needed).
     *        This method is called during system initialization to prepare the relay for operation.
     */
    void initialize() override;

private:
    /**
     * @brief Set the relay state.
     * @param newState The new state to set (open or closed).
     */
    void setRelayState(cobold::actuators::RelayState newState);
};


