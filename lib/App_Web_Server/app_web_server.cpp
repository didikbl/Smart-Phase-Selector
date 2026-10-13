/**
 * @file app_web_server.cpp
 * @brief HTTP server implementation for the Smart Phase Selector.
 *
 * Provides the WebUI, publishes the latest system state and receives
 * selection commands from the client.
 *
 * The orchestrator is responsible for system decisions. This module
 * only stores and exposes system data and transports WebUI commands.
 */

#include "app_web_server.h"

//------------------------------------------------ GLOBAL VARIABLES

static AsyncWebServer server(80);

static bool routes_registered = false;
static bool server_started = false;

/**
 * @brief Stores the latest voltage measurement for each phase.
 *
 * Indexes: 0 = phase 1, 1 = phase 2, 2 = phase 3.
 */
static float input_voltage[3] = {0.0f, 0.0f, 0.0f};

/**
 * @brief Stores the latest status of each phase.
 */
static voltage_status_t phase_voltage_status[3] = {
    NORMAL,
    NORMAL,
    NORMAL
};

/**
 * @brief Stores the latest global system status.
 */
static system_status_t current_system_status = SYSTEM_NORMAL;

/**
 * @brief Stores the latest system error code.
 */
static system_error_t current_system_error = NO_ERROR;

/**
 * @brief Stores the selection mode confirmed by the orchestrator.
 */
static selection_mode_t current_selection_mode = AUTO_MODE;

/**
 * @brief Stores a pending mode command received from the WebUI.
 */
static selection_mode_t requested_mode = AUTO_MODE;
static bool mode_command_pending = false;

/**
 * @brief Stores a pending manual phase command received from the WebUI.
 */
static selected_phase_t requested_phase = NO_PHASE_SELECTED;
static bool phase_command_pending = false;

//------------------------------------------------ PRIVATE HELPERS

/**
 * @brief Converts a voltage status to its JSON string representation.
 */
static const char *web_server_voltage_status_to_string(voltage_status_t status)
{
    switch (status)
    {
        case UNDERVOLTAGE:
            return "UNDERVOLTAGE";

        case NORMAL:
            return "NORMAL";

        case OVERVOLTAGE:
            return "OVERVOLTAGE";

        default:
            return "UNKNOWN";
    }
}

/**
 * @brief Converts the global system status to its JSON representation.
 */
static const char *web_server_system_status_to_string(
    system_status_t status)
{
    switch (status)
    {
        case SYSTEM_NORMAL:
            return "NORMAL";

        case FAULT:
            return "FAULT";

        default:
            return "UNKNOWN";
    }
}

/**
 * @brief Converts the system error code to its JSON representation.
 */
static const char *web_server_system_error_to_string(
    system_error_t error)
{
    switch (error)
    {
        case NO_ERROR:
            return "NO_ERROR";

        case VOLTAGE_SENSOR_READ_ERROR:
            return "VOLTAGE_SENSOR_READ_ERROR";

        case INVALID_VOLTAGE_MEASUREMENTS:
            return "INVALID_VOLTAGE_MEASUREMENTS";

        default:
            return "UNKNOWN_ERROR";
    }
}

/**
 * @brief Converts the selection mode to its JSON representation.
 */
static const char *web_server_selection_mode_to_string(
    selection_mode_t mode)
{
    switch (mode)
    {
        case AUTO_MODE:
            return "AUTO_MODE";

        case MANUAL_MODE:
            return "MANUAL_MODE";

        default:
            return "UNKNOWN";
    }
}

/**
 * @brief Parses a selection mode received from the WebUI.
 *
 * @param value String representation of the requested mode.
 * @param mode Pointer receiving the parsed mode.
 * @return true if the mode is valid.
 */
static bool web_server_parse_selection_mode(const String &value, selection_mode_t *mode)
{
    if (mode == nullptr)
    {
        return false;
    }

    if (value == "AUTO_MODE")
    {
        *mode = AUTO_MODE;
        return true;
    }

    if (value == "MANUAL_MODE")
    {
        *mode = MANUAL_MODE;
        return true;
    }

    return false;
}

/**
 * @brief Parses a manually requested phase received from the WebUI.
 *
 * @param value String representation of the requested phase.
 * @param phase Pointer receiving the parsed phase.
 * @return true if the phase is valid.
 */
static bool web_server_parse_requested_phase(const String &value, selected_phase_t *phase)
{
    if (phase == nullptr)
    {
        return false;
    }

    if (value == "PHASE_1_SELECTED")
    {
        *phase = PHASE_1_SELECTED;
        return true;
    }

    if (value == "PHASE_2_SELECTED")
    {
        *phase = PHASE_2_SELECTED;
        return true;
    }

    if (value == "PHASE_3_SELECTED")
    {
        *phase = PHASE_3_SELECTED;
        return true;
    }

    return false;
}

//------------------------------------------------ INITIALIZATION

/**
 * @brief Initializes the HTTP server.
 *
 * Registers the routes and starts the server.
 *
 * @return true if initialization is completed.
 */
bool web_server_init()
{
    if (server_started)
    {
        return true;
    }

    web_server_register_routes();

    server.begin();
    server_started = true;

    message_println("[WEB SERVER STARTED]");
    message_println("[WEB SERVER RUNNING]");

    return true;
}

//------------------------------------------------ ROUTE REGISTRATION

/**
 * @brief Registers the HTTP routes handled by the server.
 *
 * GET  /             : Serves the WebUI.
 * GET  /fetch-data   : Returns the latest system state.
 * POST /post-data    : Receives WebUI commands.
 */
void web_server_register_routes()
{
    if (routes_registered)
    {
        return;
    }

    server.on("/", HTTP_GET, web_server_handle_root);

    server.on("/fetch-data", HTTP_GET, web_server_handle_get_data);

    server.on("/post-data", HTTP_POST, web_server_handle_post_data);

    routes_registered = true;
}

//------------------------------------------------ GET DATA HANDLER

/**
 * @brief Handles GET requests for the latest system data.
 *
 * Returns phase voltages, individual voltage statuses, global system
 * status, system error code and the mode confirmed by the orchestrator.
 *
 * @param request Pointer to the incoming HTTP request.
 */
void web_server_handle_get_data(AsyncWebServerRequest *request)
{
    JsonDocument doc;

    JsonObject voltages = doc["voltages"].to<JsonObject>();
    voltages["phase1"] = input_voltage[0];
    voltages["phase2"] = input_voltage[1];
    voltages["phase3"] = input_voltage[2];

    JsonObject statuses = doc["voltageStatus"].to<JsonObject>();
    statuses["phase1"] = web_server_voltage_status_to_string(phase_voltage_status[0]);
    statuses["phase2"] = web_server_voltage_status_to_string(phase_voltage_status[1]);
    statuses["phase3"] = web_server_voltage_status_to_string(phase_voltage_status[2]);

    doc["systemStatus"] = web_server_system_status_to_string(current_system_status);
    doc["systemError"] = web_server_system_error_to_string(current_system_error);
    doc["selectionMode"] = web_server_selection_mode_to_string(current_selection_mode);

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);

    message_println("[WEB SERVER] System data sent.");
}

//------------------------------------------------ POST DATA HANDLER

/**
 * @brief Handles POST requests containing WebUI commands.
 *
 * Accepts the following form parameters:
 * - selectionMode: AUTO_MODE or MANUAL_MODE.
 * - requestedPhase: PHASE_1_SELECTED, PHASE_2_SELECTED or
 *   PHASE_3_SELECTED.
 *
 * These values represent requests, not confirmed system state.
 *
 * @param request Pointer to the incoming HTTP request.
 */
void web_server_handle_post_data(AsyncWebServerRequest *request)
{
    const bool has_mode = request->hasParam("selectionMode", true);
    const bool has_phase = request->hasParam("requestedPhase", true);

    if (!has_mode && !has_phase)
    {
        request->send(
            400,
            "text/plain",
            "Missing selectionMode or requestedPhase parameter"
        );

        message_println("[WEB SERVER] Missing command parameter.");
        return;
    }

    selection_mode_t new_mode = AUTO_MODE;
    selected_phase_t new_phase = NO_PHASE_SELECTED;

    if (has_mode)
    {
        const String mode_value =
            request->getParam("selectionMode", true)->value();

        if (!web_server_parse_selection_mode(mode_value, &new_mode))
        {
            request->send(400, "text/plain", "Invalid selectionMode");
            message_println("[WEB SERVER] Invalid selection mode.");
            return;
        }
    }

    if (has_phase)
    {
        const String phase_value =
            request->getParam("requestedPhase", true)->value();

        if (!web_server_parse_requested_phase(phase_value, &new_phase))
        {
            request->send(400, "text/plain", "Invalid requestedPhase");
            message_println("[WEB SERVER] Invalid requested phase.");
            return;
        }
    }

    // Store valid commands for retrieval by the orchestrator.
    if (has_mode)
    {
        requested_mode = new_mode;
        mode_command_pending = true;
    }

    if (has_phase)
    {
        requested_phase = new_phase;
        phase_command_pending = true;
    }

    message_println("[WEB SERVER] Valid command received.");

    request->send(200, "text/plain", "Command received");
}

//------------------------------------------------ SYSTEM DATA UPDATE

/**
 * @brief Updates the system data exposed to the WebUI.
 *
 * Copies the latest values supplied by the orchestrator. This function
 * does not interpret voltages or make selection decisions.
 *
 * @param voltages Array containing three phase voltage measurements.
 * @param voltage_status Array containing three phase voltage statuses.
 * @param system_status Current global system status.
 * @param system_error Current system error code.
 * @param selection_mode Mode currently confirmed by the orchestrator.
 */
void web_server_update_system_data(
    const float voltages[3],
    const voltage_status_t voltage_status[3],
    system_status_t system_status,
    system_error_t system_error,
    selection_mode_t selection_mode)
{
    if (voltages == nullptr || voltage_status == nullptr)
    {
        return;
    }

    for (size_t i = 0; i < 3; i++)
    {
        input_voltage[i] = voltages[i];
        phase_voltage_status[i] = voltage_status[i];
    }

    current_system_status = system_status;
    current_system_error = system_error;
    current_selection_mode = selection_mode;
}

//------------------------------------------------ MODE COMMAND RETRIEVAL

/**
 * @brief Retrieves and consumes a pending selection mode command.
 *
 * @param mode Pointer receiving the requested mode.
 * @return true if a new mode command is available.
 */
bool web_server_get_requested_mode(selection_mode_t *mode)
{
    if (mode == nullptr || !mode_command_pending)
    {
        return false;
    }

    *mode = requested_mode;
    mode_command_pending = false;

    return true;
}

//------------------------------------------------ PHASE COMMAND RETRIEVAL

/**
 * @brief Retrieves and consumes a pending manual phase command.
 *
 * @param phase Pointer receiving the requested phase.
 * @return true if a new phase command is available.
 */
bool web_server_get_requested_phase(selected_phase_t *phase)
{
    if (phase == nullptr || !phase_command_pending)
    {
        return false;
    }

    *phase = requested_phase;
    phase_command_pending = false;

    return true;
}

//------------------------------------------------ SIMULATION

/**
 * @brief Loads sample system data for standalone WebUI testing.
 *
 * @note Do not use alongside live orchestrator updates.
 */
void web_server_simulate_system_data()
{
    const float simulated_voltages[3] = {
        220.0f,
        195.0f,
        252.0f
    };

    const voltage_status_t simulated_statuses[3] = {
        NORMAL,
        UNDERVOLTAGE,
        OVERVOLTAGE
    };

    web_server_update_system_data(
        simulated_voltages,
        simulated_statuses,
        SYSTEM_NORMAL,
        NO_ERROR,
        AUTO_MODE
    );

    message_println("[WEB SERVER] Simulation data loaded.");
}

//------------------------------------------------ HOME PAGE HANDLER

/**
 * @brief Serves the main WebUI page.
 *
 * @param request Pointer to the incoming HTTP request.
 */
void web_server_handle_root(AsyncWebServerRequest *request)
{
    if (!LittleFS.exists("/index.html"))
    {
        request->send(404, "text/plain", "WebUI file not found");
        message_println("[WEB SERVER] /index.html not found.");
        return;
    }

    request->send(LittleFS, "/index.html", "text/html");
}
