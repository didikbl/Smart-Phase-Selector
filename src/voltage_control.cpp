#include "voltage_control.h"

constexpr float UNDERVOLTAGE_MAX_VOLTAGE = 198.0f;

constexpr float OVERVOLTAGE_MIN_VOLTAGE = 250.0f;

static selection_mode_t _selection_mode = AUTO_MODE;



bool check_sensor_data(float voltage)
{
    return std::isfinite(voltage) && voltage >= 0.0f;
}


bool validate_voltage_measurements(float phase_1,float phase_2, float phase_3)
{
    return check_sensor_data(phase_1) &&
           check_sensor_data(phase_2) &&
           check_sensor_data(phase_3);
}


bool check_undervoltage_status(float voltage)
{
    return voltage <= UNDERVOLTAGE_MAX_VOLTAGE;
}


bool check_overvoltage_status(float voltage)
{
    return voltage >= OVERVOLTAGE_MIN_VOLTAGE;
}

void select_optimal_phase( float phase_1, float phase_2, float phase_3, selected_phase_t *phase)
{
    if (!check_sensor_data(phase_1) || !check_sensor_data(phase_2) || !check_sensor_data(phase_3))
    {
       *phase = NO_PHASE_SELECTED;
        printf("INVALID VOLTAGE DATA\n");
        return;
    }

    std::vector<float> phases = {phase_1, phase_2, phase_3};

    for (size_t i = 0; i < phases.size(); ++i)
    {
        if (check_overvoltage_status(phases[i]))
        {
            phases[i] *= -1.0f;
            printf("OVERVOLTAGE ON PHASE_%d\n", i + 1);
        }
    }

    int phase_no = 1;

    for (float voltage : phases)
    {
        if (voltage < 0.0f) voltage *= -1.0f;

        printf("PHASE_%d: %.0f V\n", phase_no, voltage);
        phase_no++;
    }

    if (phases[0] < 0.0f && phases[1] < 0.0f && phases[2] < 0.0f)
    {
       *phase = NO_PHASE_SELECTED;
        printf("NO VALID PHASE AVAILABLE\n");
        return;
    }
    else
    {
         if (phases[0] >= phases[1] && phases[0] >= phases[2])
         {
            *phase = PHASE_1_SELECTED;
             printf("PHASE_1 SELECTED\n");
         }
         else if (phases[1] >= phases[0] && phases[1] >= phases[2])
         {
            *phase = PHASE_2_SELECTED;
             printf("PHASE_2 SELECTED\n");
         }
         else
         {
            *phase = PHASE_3_SELECTED;
             printf("PHASE_3 SELECTED\n");
         }
     }

}


void get_voltage_statuses(float phase_1, float phase_2, float phase_3, std::vector<voltage_status_t> *statuses)
{
    statuses->clear();

    if (check_overvoltage_status(phase_1))
        statuses->push_back(OVERVOLTAGE);
    else if (check_undervoltage_status(phase_1))
        statuses->push_back(UNDERVOLTAGE);
    else
        statuses->push_back(NORMAL);

    if (check_overvoltage_status(phase_2))
        statuses->push_back(OVERVOLTAGE);
    else if (check_undervoltage_status(phase_2))
        statuses->push_back(UNDERVOLTAGE);
    else
        statuses->push_back(NORMAL);

    if (check_overvoltage_status(phase_3))
        statuses->push_back(OVERVOLTAGE);
    else if (check_undervoltage_status(phase_3))
        statuses->push_back(UNDERVOLTAGE);
    else
        statuses->push_back(NORMAL);
}


void print_voltage_statuses(const std::vector<voltage_status_t>& statuses)
{
    for (size_t i = 0; i < statuses.size(); ++i)
    {
        printf("PHASE_%d: ", i + 1);

        switch (statuses[i])
        {
            case UNDERVOLTAGE:
                printf("UNDERVOLTAGE\n");
                break;

            case NORMAL:
                printf("NORMAL\n");
                break;

            case OVERVOLTAGE:
                printf("OVERVOLTAGE\n");
                break;

            default:
                printf("UNKNOWN\n");
                break;
        }
    }
}

bool is_phase_selection_changed(selected_phase_t current_phase,
                                selected_phase_t new_phase)
{
    return current_phase != new_phase;
}

bool selection_delay_elapsed(uint32_t start_time)
{
    return (millis() - start_time) >= 5000;
}

void start_selection_delay(uint32_t *start_time)
{
    *start_time = millis();
}

selection_mode_t selection_mode = AUTO_MODE;

bool set_selection_mode(selection_mode_t mode)
{
    if (mode != AUTO_MODE && mode != MANUAL_MODE)
    {
        return false;
    }

    selection_mode = mode;
    return true;
}



bool select_manual_phase(
    selected_phase_t requested_phase,
    const std::vector<voltage_status_t>& statuses,
    selected_phase_t *new_phase)
{
    if (_selection_mode != MANUAL_MODE ||
        new_phase == nullptr ||
        statuses.size() != 3)
    {
        return false;
    }

    size_t phase_index;

    switch (requested_phase)
    {
        case PHASE_1_SELECTED:
            phase_index = 0;
            break;

        case PHASE_2_SELECTED:
            phase_index = 1;
            break;

        case PHASE_3_SELECTED:
            phase_index = 2;
            break;

        default:
            return false;
    }

    if (statuses[phase_index] == OVERVOLTAGE)
    {
        printf("MANUAL SELECTION REJECTED: OVERVOLTAGE\n");
        return false;
    }

    *new_phase = requested_phase;
    return true;
}

bool is_phase_overvoltage(
    selected_phase_t current_phase,
    const std::vector<voltage_status_t>& statuses)
{
    if (statuses.size() != 3)
        return true; // Données invalides : comportement prudent

    switch (current_phase)
    {
        case PHASE_1_SELECTED:
            return statuses[0] == OVERVOLTAGE;

        case PHASE_2_SELECTED:
            return statuses[1] == OVERVOLTAGE;

        case PHASE_3_SELECTED:
            return statuses[2] == OVERVOLTAGE;

        default:
            return false;
    }
}