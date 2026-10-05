/**
 * @file main.cpp
 * @brief Entry point for the Smart Phase Selector application.
 *
 * This file initializes the embedded system and then keeps the application
 * running in the main loop.
 */

#include "phase_selector.h"
#include "app_wifi.h"

/**
 * @brief Wi-Fi SSID used for station-mode connection.
 */
static char sta_ssid[] = "S22 Ultra de Didier";

/**
 * @brief Wi-Fi password used for the station connection.
 */
static char sta_password[] = "didikabelu";

/**
 * @brief Initializes the phase selector system and all required subsystems.
 */
void setup()
{
     init_phase_selector_system();
}

/**
 * @brief Main application loop that continuously runs the system logic.
 */
void loop()
{
     run_phase_selector_app();
}

