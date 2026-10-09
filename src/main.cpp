#include "voltage_control.h"
#include <Arduino.h>
//=============================ORCHESTRATOR VARIABLES==========================================
float phase_1;
float phase_2;
float phase_3;
selected_phase_t phase_selection = NO_PHASE_SELECTED;

void setup() 
{
    
    
     
}

void loop() 
{
     

     vTaskDelay(1000 / portTICK_PERIOD_MS);
}
 



