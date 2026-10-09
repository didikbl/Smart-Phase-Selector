#ifndef VOLTAGE_CONTROL_H
#define VOLTAGE_CONTROL_H

#include <iostream>
#include <stdint.h>
#include <vector>
#include <cmath>
#include "Arduino.h"

/*@brief Enum for voltage statuses*/
typedef enum {
        UNDERVOLTAGE,
        NORMAL,
        OVERVOLTAGE
} voltage_status_t;

/*@brief Enum for sensor data statuses*/
typedef enum {
        INVALID_DATA,
        VALID_DATA,
} sensor_data_status_t;

/*@brief Enum for selected phase*/
typedef enum {
        PHASE_1_SELECTED,
        PHASE_2_SELECTED,
        PHASE_3_SELECTED,
        NO_PHASE_SELECTED

} selected_phase_t;

/*@brief Enum for selection mode*/
typedef enum {
        AUTO_MODE,
        MANUAL_MODE
} selection_mode_t;


/*
@brief Check if the sensor data is valid
@param voltage The voltage reading from the sensor
@return true if the voltage is valid, false otherwise
*/
bool check_sensor_data(float voltage);


/*@brief Validate the voltage measurements from all three phases
 * @param phase_1 Voltage reading for phase 1
 * @param phase_2 Voltage reading for phase 2
 * @param phase_3 Voltage reading for phase 3
 * @return true if all measurements are valid, false otherwise
 */
bool validate_voltage_measurements(float phase_1,float phase_2, float phase_3);

/*
@brief Check if the voltage is within the undervoltage range
@param voltage The voltage reading from the sensor
@return true if the voltage is undervoltage, false otherwise
*/
bool check_undervoltage_status(float voltage);

/*
@brief Check if the voltage is within the overvoltage range
@param voltage The voltage reading from the sensor
@return true if the voltage is overvoltage, false otherwise
*/
bool check_overvoltage_status(float voltage);

/*@brief Select the optimal phase based on voltage readings
 * @param phase_1 Voltage reading for phase 1
 * @param phase_2 Voltage reading for phase 2
 * @param phase_3 Voltage reading for phase 3
 * @param phase Pointer to the selected phase
 */
void select_optimal_phase(float phase_1, float phase_2, float phase_3, selected_phase_t *phase);

/*@brief Get the voltage statuses for all three phases
 * @param phase_1 Voltage reading for phase 1
 * @param phase_2 Voltage reading for phase 2
 * @param phase_3 Voltage reading for phase 3
 * @param statuses Pointer to the vector to store the voltage statuses
 */
void get_voltage_statuses(float phase_1, float phase_2, float phase_3, std::vector<voltage_status_t> *statuses);
 
/*@brief Print the voltage statuses for all three phases
 * @param statuses Reference to the vector containing the voltage statuses
 */
void print_voltage_statuses(const std::vector<voltage_status_t>& statuses);

/*@brief Check if the phase selection has changed
 * @param current_phase The current selected phase
 * @param new_phase The newly selected phase
 * @return true if the selection has changed, false otherwise
 */
bool is_phase_selection_changed(selected_phase_t current_phase, selected_phase_t new_phase);


/*
@brief Start the phase selection delay
 * @param start_time Pointer to the variable storing the start time
 */
void start_selection_delay(uint32_t *start_time);

/*
@brief Check if the selection delay has elapsed
 * @param start_time The start time of the delay
 * @return true if the delay has elapsed, false otherwise
 */
bool selection_delay_elapsed(uint32_t start_time);

/*@brief Set the phase selection mode
 * @param mode The desired selection mode
 * @return true if the mode was set successfully, false otherwise
 */
bool set_selection_mode(selection_mode_t mode);

/*@brief Get the current phase selection mode
 * @param mode Pointer to the variable to store the selection mode
 * @return true if the mode was retrieved successfully, false otherwise
 */
bool get_selection_mode(selection_mode_t *mode);

/*@brief Get the voltage statuses for all three phases
 * @param phase_1 Voltage reading for phase 1
 * @param phase_2 Voltage reading for phase 2
 * @param phase_3 Voltage reading for phase 3
 * @param statuses Pointer to the vector to store the voltage statuses
 */
void get_voltage_statuses(float phase_1, float phase_2, float phase_3, std::vector<voltage_status_t> *statuses);
            
/*@brief Print the voltage statuses for all three phases
 * @param statuses Reference to the vector containing the voltage statuses
 */
void print_voltage_statuses(const std::vector<voltage_status_t>& statuses);

/*@brief Check if the phase selection has changed
 * @param current_phase The current selected phase
 * @param new_phase The newly selected phase
 * @return true if the selection has changed, false otherwise
 */
bool is_phase_selection_changed(selected_phase_t current_phase, selected_phase_t new_phase);


/*@brief Start the phase selection delay
 * @param start_time Pointer to the variable storing the start time
 */
void start_selection_delay(uint32_t *start_time);

/*@brief Check if the selection delay has elapsed
 * @param start_time The start time of the delay
 * @return true if the delay has elapsed, false otherwise
 */
bool selection_delay_elapsed(uint32_t start_time);

/*@brief Set the phase selection mode
 * @param mode The desired selection mode
 * @return true if the mode was set successfully, false otherwise
 */
bool set_selection_mode(selection_mode_t mode);

/*@brief Get the current phase selection mode
 * @param mode Pointer to the variable to store the selection mode
 * @return true if the mode was retrieved successfully, false otherwise
 */
bool get_selection_mode(selection_mode_t *mode);

/*@brief Select a manual phase
 * @param requested_phase The phase requested for selection
 * @param statuses The voltage statuses for all three phases
 * @param new_phase Pointer to the variable to store the newly selected phase
 * @return true if the phase was selected successfully, false otherwise
 */
bool select_manual_phase(
     selected_phase_t requested_phase,
     const std::vector<voltage_status_t>& statuses,
     selected_phase_t *new_phase);

/*@brief Check if the specified phase is overvoltage
 * @param current_phase The phase to check
 * @param statuses The voltage statuses for all three phases
 * @return true if the phase is overvoltage, false otherwise
 */
bool is_phase_overvoltage(
     selected_phase_t current_phase,
     const std::vector<voltage_status_t>& statuses);


#endif // VOLTAGE_CONTROL_H