#pragma once

#include <cobold.hpp>

/**
 * @class SingleRelay
 * @brief Represents a single relay device.
 *        This class implements the IRelay interface and provides methods for controlling and querying the state of the relay.
 */
class SingleRelay : public cobold::actuators::IRelay
{
private:
    /**
     * @brief The pin number connected to the relay.
     * This is the pin number of the Arduino board that is connected to the relay.
     * The pin number is set during construction and cannot be changed afterwards.
     */
    int pin;

    /**
     * @brief The normal state of the relay (open or closed).
     * This is the normal state of the relay, which is either open or closed.
     * The normal state is set during construction and cannot be changed afterwards.
     * The default normal state is closed.
     * @see getNormalState()
     * @see isNormalState()
     */
    cobold::actuators::RelayState normalState;

    /**
     * @brief The current state of the relay (open or closed).
     * This is the current state of the relay, which is either open or closed
     * The default current state is closed.
     * @see getState()
     * @see setRelayState()
     *
     */
    cobold::actuators::RelayState currentState; ///< The current state (open or closed) of the relay.

    /**
     * @brief A pointer to the service collection.
     * The service collection is set during construction and cannot be changed afterwards.
    */
    ServiceCollection *services;

    /**
     * @brief Set the relay state.
     * @param newState The new state to set (open or closed).
     */
    void setRelayState(cobold::actuators::RelayState newState);

    /**
     * @brief A pointer to the logger service.
     * The logger service is set during construction and cannot be changed afterwards.
     */
    ILogger *logger;

public:
    /**
     * @brief Constructor with pin and default normal state.
     * @param relayPin The pin number connected to the relay.
     * @param defaultNormalState The default normal state of the relay (open or closed).
     */
    SingleRelay(ServiceCollection *services, int relayPin, cobold::actuators::RelayState defaultNormalState = cobold::actuators::RelayState::CLOSED);

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
};
