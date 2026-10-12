#include "orchestrator.h"
#include "Arduino.h"


void setup() 
{
 orchestrator_init();
}

void loop() 
{
    orchestrator_update();
    vTaskDelay(pdMS_TO_TICKS(2000));
}
 



