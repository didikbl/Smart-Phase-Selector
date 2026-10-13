#include <vector>
#include <Arduino.h>

#include "orchestrator.h"
#include "app_types.h"
#include "relay_manager.h"
#include "voltage_sensor.h"
#include "voltage_control.h"
#include "app_wifi.h"
#include "app_web_server.h"

/**
 * @brief Simulates voltage sensor initialization.
 * @return true if initialization succeeds.
 */
static bool voltage_sensor_init_simulated();

/**
 * @brief Simulates LCD initialization.
 * @return true if initialization succeeds.
 */
static bool lcd_manager_init_simulated();

/**
 * @brief Processes commands received from the WebUI.
 */
static void process_web_commands();

/**
 * @brief Publishes current system information to the WebUI.
 * @param phase_1 Voltage measured on phase 1.
 * @param phase_2 Voltage measured on phase 2.
 * @param phase_3 Voltage measured on phase 3.
 * @param statuses Voltage status for each phase.
 * @param system_status Overall system status.
 * @param system_error Current system error.
 */
static void publish_system_data(
    float phase_1,
    float phase_2,
    float phase_3,
    const std::vector<voltage_status_t>& statuses,
    system_status_t system_status,
    system_error_t system_error
);

/**
 * @brief Disconnects the output and resets phase selection.
 */
static void disconnect_output();

static selected_phase_t _current_phase = NO_PHASE_SELECTED;
static selected_phase_t _new_phase = NO_PHASE_SELECTED;
static selected_phase_t _requested_manual_phase = NO_PHASE_SELECTED;
static selected_phase_t _timed_phase = NO_PHASE_SELECTED;

static std::vector<voltage_status_t> _phase_statuses;

static uint32_t _selection_start_time = 0;
static bool _selection_timer_active = false;

static const char* ssid = "SMART-PHASE-SELECTOR";
static const char* password = "12345678";
static _wifi_mode_t wifi_mode = WIFI_AP_MODE;

void orchestrator_init()
{
    // 1. Initialize the output in a safe state.
    relay_manager_init();
    disconnect_output();

    // 2. Initialize voltage measurement.
    // Replace the simulated call with voltage_sensor_init()
    // when the real sensor initialization is ready.
    voltage_sensor_init_simulated();

    // 3. Initialize voltage control.
    voltage_control_init();

    // 4. Initialize the local display.
    // Replace with lcd_manager_init() when available.
    lcd_manager_init_simulated();

    // 5. Initialize networking and the WebUI.
    wifi_manager_init(ssid, password, wifi_mode);
    web_server_init();
}

void orchestrator_update()
{
    float phase_1 = 0.0f;
    float phase_2 = 0.0f;
    float phase_3 = 0.0f;

    selection_mode_t mode = AUTO_MODE;

    // 1. Process commands independently of sensor validity.
    process_web_commands();

    // 2. Read the phase voltages.
    const bool read_ok = read_voltage(
        &phase_1,
        &phase_2,
        &phase_3
    );

    // 3. Handle sensor read failures and invalid measurements.
    if (!read_ok ||
        !validate_voltage_measurements(
            phase_1,
            phase_2,
            phase_3))
    {
        disconnect_output();

        _phase_statuses.assign(
            3,
            VOLTAGE_STATUS_INVALID
        );

        const system_error_t error = read_ok
            ? INVALID_VOLTAGE_MEASUREMENTS
            : VOLTAGE_SENSOR_READ_ERROR;

        publish_system_data(
            0.0f,
            0.0f,
            0.0f,
            _phase_statuses,
            FAULT,
            error
        );

        return;
    }

    // 4. Determine the status of each phase.
    get_voltage_statuses(
        phase_1,
        phase_2,
        phase_3,
        &_phase_statuses
    );

    // Protect against an unexpected status-vector size.
    if (_phase_statuses.size() != 3)
    {
        disconnect_output();

        _phase_statuses.assign(
            3,
            VOLTAGE_STATUS_INVALID
        );

        publish_system_data(
            0.0f,
            0.0f,
            0.0f,
            _phase_statuses,
            FAULT,
            INVALID_VOLTAGE_MEASUREMENTS
        );

        return;
    }

    // 5. Read the active selection mode.
    if (!get_selection_mode(&mode))
    {
        disconnect_output();

        publish_system_data(
            phase_1,
            phase_2,
            phase_3,
            _phase_statuses,
            FAULT,
            INVALID_VOLTAGE_MEASUREMENTS
        );

        return;
    }

    // 6. Immediately disconnect if the selected phase
    // becomes overvoltage.
    if (is_phase_overvoltage(
            _current_phase,
            _phase_statuses))
    {
        disconnect_output();
    }

    // 7. Select a candidate according to the active mode.
    if (mode == AUTO_MODE)
    {
        select_optimal_phase(
            phase_1,
            phase_2,
            phase_3,
            &_new_phase
        );
    }
    else
    {
        // The manual-selection function rejects overvoltage.
        if (!select_manual_phase(
                _requested_manual_phase,
                _phase_statuses,
                &_new_phase))
        {
            _new_phase = NO_PHASE_SELECTED;
        }
    }

    // 8. No admissible phase: disconnect the output.
    if (_new_phase == NO_PHASE_SELECTED)
    {
        disconnect_output();
    }
    // 9. The requested phase is already selected.
    else if (_new_phase == _current_phase)
    {
        _selection_timer_active = false;
        _timed_phase = NO_PHASE_SELECTED;
    }
    else
    {
        // 10. Start or restart the timer whenever the
        // candidate phase changes.
        if (!_selection_timer_active ||
            _timed_phase != _new_phase)
        {
            _selection_start_time = millis();
            _selection_timer_active = true;
            _timed_phase = _new_phase;
        }
        // 11. Confirm the candidate after five stable seconds.
        else if ((uint32_t)(
                    millis() - _selection_start_time
                 ) >= 5000U)
        {
            _current_phase = _new_phase;
            _selection_timer_active = false;
            _timed_phase = NO_PHASE_SELECTED;

            relay_manager(_current_phase);
        }
    }

    // 12. Publish the latest system information.
    publish_system_data(
        phase_1,
        phase_2,
        phase_3,
        _phase_statuses,
        SYSTEM_NORMAL,
        NO_ERROR
    );
}

static void process_web_commands()
{
    selection_mode_t requested_mode;
    selected_phase_t requested_phase;

    // Apply a requested mode only if voltage_control accepts it.
    if (web_server_get_requested_mode(&requested_mode))
    {
        set_selection_mode(requested_mode);
    }

    // Keep the latest requested manual phase.
    if (web_server_get_requested_phase(&requested_phase))
    {
        _requested_manual_phase = requested_phase;
    }
}

static void publish_system_data(
    float phase_1,
    float phase_2,
    float phase_3,
    const std::vector<voltage_status_t>& statuses,
    system_status_t system_status,
    system_error_t system_error
)
{
    const float voltages[3] = {
        phase_1,
        phase_2,
        phase_3
    };

    voltage_status_t voltage_status[3] = {
        VOLTAGE_STATUS_INVALID,
        VOLTAGE_STATUS_INVALID,
        VOLTAGE_STATUS_INVALID
    };

    if (statuses.size() == 3)
    {
        for (size_t i = 0; i < 3; ++i)
        {
            voltage_status[i] = statuses[i];
        }
    }

    selection_mode_t mode = AUTO_MODE;
    get_selection_mode(&mode);

    web_server_update_system_data(
        voltages,
        voltage_status,
        system_status,
        system_error,
        mode
    );
}

static void disconnect_output()
{
    _current_phase = NO_PHASE_SELECTED;
    _new_phase = NO_PHASE_SELECTED;
    _selection_timer_active = false;
    _timed_phase = NO_PHASE_SELECTED;

    relay_manager(NO_PHASE_SELECTED);
}

static bool voltage_sensor_init_simulated()
{
    Serial.println(
        "[ORCHESTRATOR] Voltage sensor initialization simulated."
    );

    return true;
}

static bool lcd_manager_init_simulated()
{
    Serial.println(
        "[ORCHESTRATOR] LCD initialization simulated."
    );

    return true;
}
