
#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include "app_actuators.h"
#include "phase_types.h"

/**
 * @brief Initializes the relays in a safe state.
 *
 * Turns OFF both phase-selection relays and the output relay
 * to ensure that no phase is connected to the output at startup.
 *
 * @return true if initialization succeeds.
 *
 * @note This implementation assumes relay_off() can safely
 *       command the configured GPIOs. If the GPIO driver exposes
 *       initialization errors, they should be checked here.
 */
bool relay_manager_init();

/*
 * @brief Manages the relays based on the confirmed phase.
 * @param phase The currently confirmed phase.
 */
bool relay_manager(selected_phase_t phase);

#endif // RELAY_MANAGER_H

