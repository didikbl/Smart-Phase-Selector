<<<<<<< HEAD
#include "relay_manager.h"

static selected_phase_t phase = NO_PHASE_SELECTED;

void setup() 
{

=======
#include "voltage_control.h"
#include <Arduino.h>
//=============================ORCHESTRATOR VARIABLES==========================================
float phase_1;
float phase_2;
float phase_3;
selected_phase_t phase_selection = NO_PHASE_SELECTED;

void setup() 
{
    
    
     
>>>>>>> feature/voltage-validation-classification
}

void loop() 
{
<<<<<<< HEAD
    relay_manager(phase);
    vTaskDelay(pdMS_TO_TICKS(1000));
=======
     

     vTaskDelay(1000 / portTICK_PERIOD_MS);
>>>>>>> feature/voltage-validation-classification
}
 



