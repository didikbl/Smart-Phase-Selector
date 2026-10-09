
#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include "app_actuators.h"
#include "phase_types.h"

/*
 * @brief Initializes relay outputs in their defined safe state.
 * @return true if initialization succeeds, false otherwise.
 */
bool relay_manager_init();

/*
 * @brief Manages the relays based on the confirmed phase.
 * @param phase The currently confirmed phase.
 */
void relay_manager(selected_phase_t phase);

#endif // RELAY_MANAGER_H

