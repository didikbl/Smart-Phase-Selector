#ifndef VOLTAGE_SENSOR_H
#define VOLTAGE_SENSOR_H

typedef enum
{
    VOLTAGE_SENSOR_SIMULATION,
    VOLTAGE_SENSOR_ANALOG_CONDITIONING,
    VOLTAGE_SENSOR_AC_MODULE
} voltage_sensor_mode_t;

/**
 * @brief Initialize the voltage sensor with the selected method.
 * @return true if initialization succeeds, false otherwise.
 */
bool voltage_sensor_init(voltage_sensor_mode_t mode);

/**
 * @brief Read the three phase voltages.
 * @param phase_1 Pointer to phase 1 voltage in volts.
 * @param phase_2 Pointer to phase 2 voltage in volts.
 * @param phase_3 Pointer to phase 3 voltage in volts.
 * @return true if the reading succeeds, false otherwise.
 */
bool read_voltage(float *phase_1,
                  float *phase_2,
                  float *phase_3);

/**
 * @brief Configure simulated voltage values for testing.
 */
bool voltage_sensor_set_simulated_values(float phase_1,
                                         float phase_2,
                                         float phase_3);

#endif