#ifndef APP_TYPES_H
#define APP_TYPES_H
#include "Arduino.h"
//----------------------------------------------------ACTUATORS-----------------------------------------------

typedef enum {
        ACTUATOR_OFF,
        ACTUATOR_ON
} actuator_state_t;

typedef enum {
        ACTUATOR_MODE_STATIC,
        ACTUATOR_MODE_BLINK,
        ACTUATOR_MODE_PWM
} actuator_mode_t;

//-----------------------------------------SENSORS--------------------------------------------------------------
typedef enum{
        SENSOR_AC_VOLTAGE,
        SENSOR_AC_CURRENT,
        SENSOR_SMOKE_DIGITAL,
        SENSOR_SMOKE_ANALOG,
        SENSOR_TEMPERATURE
} sensor_id_t;

//-------------------------------------------------SYSTEM EVENTS-------------------------------------------------------------
typedef enum {
        EVENT_VOLTAGE_HIGH,
        EVENT_VOLTAGE_LOW,
        EVENT_FAULT_OVERLOAD,
        EVENT_FAULT_SHORT_CIRCUIT,
        EVENT_TRANSIENT_SPIKE,
        EVENT_UNKNOWN
} event_id_t;

typedef enum{
        ACTIVE_LINE_1,
        ACTIVE_LINE_2, 
        ACTIVE_LINE_3,
        LINE_1_INACTIVE,
        LINE_2_INACTIVE,
        LINE_3_INACTIVE,
        NO_ACTIVE_LINE
} active_line_t;

typedef enum{
        LINE_1,
        LINE_2,
        LINE_3 
} line_t;

//--------------------------------------------GPIO MAPPING----------------------------------------------------------
typedef enum{
//---------SAFE IO GPIO----------------
        GPIO_PIN_13 = 13,
        GPIO_PIN_14 = 14,
        GPIO_PIN_25 = 25,
        GPIO_PIN_26 = 26,
        GPIO_PIN_27 = 27,
        GPIO_PIN_32 = 32,
        GPIO_PIN_33 = 33,
        GPIO_PIN_34 = 34,//---------INPUT ONLY----------------
        GPIO_PIN_35 = 35,//---------INPUT ONLY----------------
        GPIO_PIN_36 = 36,//---------INPUT ONLY----------------
        GPIO_PIN_39 = 39,//---------INPUT ONLY----------------

} gpio_pin_t;

//--------------------------------------WIFI MANAGER---------------------------------------------------------------

typedef enum
 {
   RUN_ON_AP,
   RUN_ON_STA,
   RUN_ON_WIFI_OFF

 }_wifi_running_mode_t;

typedef enum{
        WIFI_AP_MODE,
        WIFI_STA_MODE,
        WIFI_AP_STA_MODE,
        WIFI_IDLE_MODE
} _wifi_mode_t;

typedef enum{
        APP_OK,
        APP_FAIL,
} app_err_t;


#endif