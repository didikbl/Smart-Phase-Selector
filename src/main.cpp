#include "phase_selector.h"
#include "app_wifi.h"
//-------------------------------------------TEST STATION MODE-------------------------------------------
static char sta_ssid []= "S22 Ultra de Didier";
static char sta_password [] = "didikabelu";

void setup() 
{
     init_phase_selector_system();
    
     
}

void loop() 
{
     run_phase_selector_app();
}
 



