#ifndef APP_MAIN_H
#define APP_MAIN_H
#include <Arduino.h>
#include "app_types.h"
#include "app_web_server.h"
#include "app_actuators.h"
#include "app_file_system.h"
#include "app_types.h"

//-----------------OUTPUT PINS---------------------------------
#define LINE_1_LED_PIN GPIO_PIN_33
#define LINE_2_LED_PIN GPIO_PIN_27
#define LINE_3_LED_PIN GPIO_PIN_26

//-------------------------------------------TEST STATION MODE-------------------------------------------
static _wifi_running_mode_t get_wifi_running_mode();

static float input_voltage [3];


void init_phase_selector_system();

void run_phase_selector_app();

static void read_sensor(sensor_id_t sensor_id);

static void publish_sensor_data(sensor_id_t sensor_id);

static  active_line_t check_active_line();

static void set_active_line();

#endif 