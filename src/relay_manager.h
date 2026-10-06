#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H
#include "app_actuators.h"

typedef enum {
        PHASE_1_SELECTED,
        PHASE_2_SELECTED,
        PHASE_3_SELECTED,
        NO_PHASE_SELECTED

} selected_phase_t;

/*
@brief Manages the relays based on the selected phase
@param phase The selected phase
*/
void relay_manager(selected_phase_t phase);

#endif // RELAY_MANAGER_H