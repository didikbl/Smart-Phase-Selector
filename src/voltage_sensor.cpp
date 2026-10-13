#include "voltage_sensor.h"
#include <cmath>

static voltage_sensor_mode_t _sensor_mode = VOLTAGE_SENSOR_SIMULATION;

static float _phase_1_voltage = 230.0f;
static float _phase_2_voltage = 215.0f;
static float _phase_3_voltage = 250.0f;

bool voltage_sensor_init(voltage_sensor_mode_t mode)
{
    switch (mode)
    {
        case VOLTAGE_SENSOR_SIMULATION:
            _sensor_mode = mode;
            return true;

        case VOLTAGE_SENSOR_ANALOG_CONDITIONING:
        case VOLTAGE_SENSOR_AC_MODULE:
        default:
            return false;
    }
}

bool read_voltage(float *phase_1,
                  float *phase_2,
                  float *phase_3)
{
    if (phase_1 == nullptr ||
        phase_2 == nullptr ||
        phase_3 == nullptr)
    {
        return false;
    }

    if (_sensor_mode != VOLTAGE_SENSOR_SIMULATION)
    {
        return false;
    }

    *phase_1 = _phase_1_voltage;
    *phase_2 = _phase_2_voltage;
    *phase_3 = _phase_3_voltage;

    return true;
}

bool voltage_sensor_set_simulated_values(float phase_1,
                                         float phase_2,
                                         float phase_3)
{
    if (!std::isfinite(phase_1) || phase_1 < 0.0f ||
        !std::isfinite(phase_2) || phase_2 < 0.0f ||
        !std::isfinite(phase_3) || phase_3 < 0.0f)
    {
        return false;
    }

    _phase_1_voltage = phase_1;
    _phase_2_voltage = phase_2;
    _phase_3_voltage = phase_3;

    return true;
}