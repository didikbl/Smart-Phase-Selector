```cpp
#include <Arduino.h>
#include "orchestrator.h"
#include "relay_manager.h"
#include "voltage_sensor.h"
#include "voltage_control.h"
#include "lcd_manager.h"
#include "wifi_manager.h"
#include "web_server.h"

void orchestrator_init()
{
    // 1. Put the output in a safe state.
    relay_manager_init();

    // 2. Initialize the voltage measurement system.
    voltage_sensor_init();

    // 3. Initialize voltage control.
    voltage_control_init();

    // 4. Initialize the local display.
    //lcd_manager_init();

    // 5. Initialize optional network services.
   // wifi_manager_init();

    web_server_init();
}

void orchestrator_update()
{
    // Application cycle will be implemented next.
}
