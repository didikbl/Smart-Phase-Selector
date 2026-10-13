
#ifndef APP_WEB_SERVER_H
#define APP_WEB_SERVER_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "app_wifi.h"
#include "app_system_log.h"
#include "app_file_system.h"
#include "app_types.h"

/**
 * @brief Initializes the web server and registers its routes.
 *
 * @return true if initialization succeeds.
 */
bool web_server_init();

/**
 * @brief Registers the HTTP routes handled by the web server.
 */
void web_server_register_routes();

/**
 * @brief Updates the system data exposed to the WebUI.
 *
 * @param voltages Array containing the three phase voltage measurements.
 * @param voltage_status Array containing the status of each phase.
 * @param system_status Current global system status.
 * @param system_error Current system error code.
 * @param selection_mode Current selection mode.
 */
void web_server_update_system_data(
     const float voltages[3],
     const voltage_status_t voltage_status[3],
     system_status_t system_status,
     system_error_t system_error,
     selection_mode_t selection_mode
);

/**
 * @brief Handles GET requests for the latest system data.
 *
 * Sends the latest available system state and error information
 * to the WebUI as JSON.
 *
 * @param request Pointer to the incoming HTTP request.
 */
void web_server_handle_get_data(AsyncWebServerRequest *request);

/**
 * @brief Handles POST requests containing WebUI commands.
 *
 * Parses and validates commands received from the WebUI.
 *
 * @param request Pointer to the incoming HTTP request.
 */
void web_server_handle_post_data(AsyncWebServerRequest *request);

/**
 * @brief Retrieves and consumes the latest requested selection mode.
 *
 * @param mode Pointer to the variable receiving the requested mode.
 * @return true if a new valid mode command is available; false otherwise.
 */
bool web_server_get_requested_mode(selection_mode_t *mode);

/**
 * @brief Retrieves and consumes the latest manually requested phase.
 *
 * @param phase Pointer to the variable receiving the requested phase.
 * @return true if a new valid phase command is available; false otherwise.
 */
bool web_server_get_requested_phase(selected_phase_t *phase);

/**
 * @brief Serves the main WebUI page.
 *
 * @param request Pointer to the incoming HTTP request.
 */
void web_server_handle_root(AsyncWebServerRequest *request);

/**
 * @brief Loads sample system data for standalone WebUI testing.
 *
 * @note Use only in simulation mode, not alongside live orchestrator updates.
 */
void web_server_simulate_system_data();

#endif // APP_WEB_SERVER_H