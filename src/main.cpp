<<<<<<< HEAD
<<<<<<< HEAD
#include "relay_manager.h"

static selected_phase_t phase = NO_PHASE_SELECTED;

void setup() 
{

=======
#include "voltage_control.h"
=======

>>>>>>> feature/voltage-sensor
#include <Arduino.h>

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
 



