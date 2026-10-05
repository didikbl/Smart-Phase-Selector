#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "app_wifi.h"
#include "app_system_log.h"
#include "app_file_system.h"
#include "app_types.h"

/**
 * @brief Holds the timestamp used when the web server startup attempt begins.
 *
 * This value is primarily used for retry or timeout tracking during the server
 * initialization lifecycle.
 */
static unsigned long _start_attempt_time;

/**
 * @brief Registers the HTTP routes served by the application.
 *
 * This function wires the request handlers exposed by the embedded frontend,
 * including the main page and the data endpoints.
 */
void setup_roots();

/**
 * @brief Starts the asynchronous web server and begins listening on the configured port.
 */
void run_webserver();

/**
 * @brief Returns the latest voltage readings to the client in JSON format.
 *
 * @param request HTTP request for the /fetch-data endpoint.
 */
void webserver_update_data(AsyncWebServerRequest *request);

/**
 * @brief Parses the posted line-selection payload from the client.
 *
 * The expected request contains a "data" parameter indicating the selected line
 * or its inactive state.
 *
 * @param request HTTP request for the /post-data endpoint.
 */
void webserver_parse_data(AsyncWebServerRequest *request);

/**
 * @brief Stores the most recent line voltages used by the web interface.
 *
 * @param value_1 Voltage measured on line 1.
 * @param value_2 Voltage measured on line 2.
 * @param value_3 Voltage measured on line 3.
 */
void webserver_get_data(const float value_1, const float value_2, const float value_3);

/**
 * @brief Converts the selected line value into the corresponding active-line enum.
 *
 * @return The active line state represented by the last received selection.
 */
active_line_t webserver_get_active_line();

/**
 * @brief Serves the main dashboard page from the file system.
 *
 * @param request HTTP request for the root route.
 */
void webserver_home(AsyncWebServerRequest*request);

/**
 * @brief Alias handler for the default application homepage.
 *
 * This route currently forwards to the same HTML page as @ref webserver_home.
 *
 * @param request HTTP request for the example home route.
 */
void webserver_home_example(AsyncWebServerRequest*request);

#endif