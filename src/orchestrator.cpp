#include <vector>
#include <Arduino.h>
#include "orchestrator.h"
/*#include "relay_manager.h"
#include "voltage_sensor.h"
#include "voltage_control.h"
#include "lcd_manager.h"
#include "wifi_manager.h"*/
#include "app_web_server.h"
#include "phase_types.h"


/**
 * @brief Simulates voltage sensor initialization.
 * @return true if the simulated initialization succeeds.
 */
static bool voltage_sensor_init_simulated();

/**
 * @brief Simulates LCD manager initialization.
 * @return true if the simulated initialization succeeds.
 */
static bool lcd_manager_init_simulated();

static selected_phase_t _current_phase = NO_PHASE_SELECTED;
static selected_phase_t _new_phase = NO_PHASE_SELECTED;

static std::vector<voltage_status_t> _phase_statuses;

static uint32_t _selection_start_time = 0;
static bool _selection_timer_active = false;


static const char* ssid = "ESP-32-AP";
static const char* password = "12345678";
static _wifi_mode_t wifi_mode = WIFI_AP_MODE;   

void orchestrator_init()
{
    // 1. Put the output in a safe state.
    //relay_manager_init();

    // 2. Initialize the voltage measurement system.
    //voltage_sensor_init();
    voltage_sensor_init_simulated();

    // 3. Initialize voltage control.
    //voltage_control_init();

    // 4. Initialize the local display.
    //lcd_manager_init();
    lcd_manager_init_simulated();
    

    // 5. Initialize optional network services.
    wifi_manager_init(ssid, password, wifi_mode);

    web_server_init();
}

void orchestrator_update()
{
    float phase_1 = 0.0f;
    float phase_2 = 0.0f;
    float phase_3 = 0.0f;

    selection_mode_t mode;

    // 1. Read the three phase voltages.
    bool read_ok = read_voltage(&phase_1, &phase_2, &phase_3);

    // 2. Validate the measurements.
    if (!read_ok ||
        !validate_voltage_measurements(phase_1, phase_2, phase_3))
    {
        // Invalid measurements: disconnect the output.
        _current_phase = NO_PHASE_SELECTED;
        _new_phase = NO_PHASE_SELECTED;
        _selection_timer_active = false;

        relay_manager(NO_PHASE_SELECTED);
        return;
    }

    // 3. Determine the status of each phase.
    get_voltage_statuses(
        phase_1,
        phase_2,
        phase_3,
        &_phase_statuses
    );

    // 4. Protect the currently selected phase against overvoltage.
    if (is_phase_overvoltage(_current_phase, _phase_statuses))
    {
        _current_phase = NO_PHASE_SELECTED;
        _new_phase = NO_PHASE_SELECTED;
        _selection_timer_active = false;

        relay_manager(NO_PHASE_SELECTED);
    }

    // 5. Read the current selection mode.
    if (!get_selection_mode(&mode))
    {
        return;
    }

    // 6. Select a candidate phase in AUTO mode.
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
        // Manual selection will be connected to the WebUI later.
        _new_phase = _current_phase;
    }

    // 7. No admissible phase: keep the output disconnected.
    if (_new_phase == NO_PHASE_SELECTED)
    {
        _current_phase = NO_PHASE_SELECTED;
        _selection_timer_active = false;

        relay_manager(NO_PHASE_SELECTED);
        return;
    }

    // 8. No change requested: no switching is necessary.
    if (_new_phase == _current_phase)
    {
        _selection_timer_active = false;
        return;
    }

    // 9. Start or restart the 5-second stability timer.
    if (!_selection_timer_active)
    {
        _selection_start_time = millis();
        _selection_timer_active = true;
        return;
    }

    // 10. Confirm the candidate only after 5 seconds.
    if ((uint32_t)(millis() - _selection_start_time) >= 5000U)
    {
        _current_phase = _new_phase;
        _selection_timer_active = false;

        // Only the confirmed phase reaches the relay manager.
        relay_manager(_current_phase);
    }
}

static bool voltage_sensor_init_simulated()
{
    Serial.println("[ORCHESTRATOR] Voltage sensor initialization simulated.");
    return true;
}


static bool lcd_manager_init_simulated()
{
    Serial.println("[ORCHESTRATOR] LCD initialization simulated.");
    return true;
}

