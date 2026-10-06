#include "relay_manager.h"
/*
 * @brief Manages the relays based on the selected phase
 * @param phase The selected phase
 */

static gpio_pin_t relay_1_pin = GPIO_PIN_25; 
static gpio_pin_t relay_2_pin = GPIO_PIN_26; 
static gpio_pin_t relay_3_pin = GPIO_PIN_27; 

void relay_manager(selected_phase_t phase) {
    // Implementation for managing relays based on selected phase
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
            relay_off(relay_1_pin);
            relay_off(relay_2_pin);
            relay_on(relay_3_pin);
            break;
    }
}