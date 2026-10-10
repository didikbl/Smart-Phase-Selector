#include "relay_manager.h"

/**
 * @file relay_manager.cpp
 * @brief Manages phase selection and output switching through relays.
 *
 * Two relays are used to select one of the three input phases.
 * Their electrical wiring provides interlocking to prevent
 * multiple phases from being connected to the output simultaneously.
 *
 * A third relay controls the output connection.
 */

/// @brief GPIO assigned to the first phase-selection relay.
static gpio_pin_t relay_1_pin = GPIO_PIN_25;

/// @brief GPIO assigned to the second phase-selection relay.
static gpio_pin_t relay_2_pin = GPIO_PIN_26;

/// @brief GPIO assigned to the output relay.
static gpio_pin_t relay_3_pin = GPIO_PIN_27;

/**
 * @brief Applies the relay configuration for the selected phase.
 *
 * Configures the two phase-selection relays and the output relay
 * according to the requested phase.
 *
 * @param phase Phase to select:
 *              - PHASE_1_SELECTED: both selection relays OFF,
 *                output relay ON.
 *              - PHASE_2_SELECTED: relay 1 ON, relay 2 OFF,
 *                output relay ON.
 *              - PHASE_3_SELECTED: both selection relays ON,
 *                output relay ON.
 *              - NO_PHASE_SELECTED: all relays OFF.
 *
 * @note The electrical interlocking is provided by the hardware
 *       wiring and must prevent simultaneous connection of input phases.
 */
bool relay_manager(selected_phase_t phase)
{
    switch (phase) {
        case PHASE_1_SELECTED:
             relay_off(relay_1_pin);
             relay_off(relay_2_pin);
             relay_on(relay_3_pin);
             break;

        case PHASE_2_SELECTED:
             relay_on(relay_1_pin);
             relay_off(relay_2_pin);
             relay_on(relay_3_pin);
             break;

        case PHASE_3_SELECTED:
             relay_on(relay_1_pin);
             relay_on(relay_2_pin);
             relay_on(relay_3_pin);
             break;

        case NO_PHASE_SELECTED:
             relay_off(relay_1_pin);
             relay_off(relay_2_pin);
             relay_off(relay_3_pin);
             break;

        default:
            // Invalid phase: disconnect the output for safety.
            relay_off(relay_1_pin);
            relay_off(relay_2_pin);
            relay_off(relay_3_pin);
            break;
    }
    return true;
}

bool relay_manager_init()
{
    relay_off(relay_1_pin);
    relay_off(relay_2_pin);
    relay_off(relay_3_pin);

    return true;
}