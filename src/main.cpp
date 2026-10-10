#include "relay_manager.h"

static selected_phase_t phase = NO_PHASE_SELECTED;

void setup() 
{

}

void loop() 
{
    relay_manager(phase);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
 



