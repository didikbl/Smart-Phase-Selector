#ifndef VOLTAGE_SENSOR_H
#define VOLTAGE_SENSOR_H

#include <stdbool.h>

/**
 * @brief Read the three phase voltages.
 *
 * @param phase_1 Pointer to phase 1 voltage in volts.
 * @param phase_2 Pointer to phase 2 voltage in volts.
 * @param phase_3 Pointer to phase 3 voltage in volts.
 * @return true if the measurements were acquired successfully,
 *         false otherwise.
 */
bool read_voltage(float *phase_1,
                  float *phase_2,
                  float *phase_3);

#endif