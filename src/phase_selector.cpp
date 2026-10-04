#include "phase_selector.h"

static _wifi_running_mode_t running_mode = RUN_ON_AP;

//-------------------------------------------TEST STATION MODE-------------------------------------------
static char sta_ssid []= "S22 Ultra de Didier";
static char sta_password [] = "didikabelu";
//-------------------------------------------TEST AP MODE-------------------------------------------
static char ap_ssid []= "SMART ELECTRIC DEVICE";
static char ap_password [] = "12345678";
static app_err_t err;


static _wifi_running_mode_t get_wifi_running_mode(){
       return running_mode;
}

void init_phase_selector_system()
{
       
       init_log_system(115200);
       init_fs();
       get_wifi_running_mode();
       
       switch (running_mode)
       {
        case RUN_ON_AP:
             err = _wifi_start_ap(ap_ssid, ap_password);
             if(err != APP_OK)
             {
                message_println("[ERROR WEBSERVER]");
                message_println("[PLEASE REBOOT....]");
             }
             else
             {
              run_webserver();
              message_println("[SERVER RUNNING.....]");
             }
        break;

        case RUN_ON_STA:
             err = _wifi_start_sta(ap_ssid, ap_password);
             if(err != APP_OK)
             {
                message_println("[ERROR WEBSERVER]");
                message_println("[PLEASE REBOOT....]");
             }
             else
             {
              
              run_webserver();
              message_println("[SERVER RUNNING.....]");
             }
        break;
       
        default:
               message_println("[WIFI MODULE : OFF]");
        break;
       }
       _wifi_report();
}

static void read_sensor(sensor_id_t sensor_id)
{
     input_voltage [LINE_1] = 235;
     input_voltage [LINE_2] = 245;
     input_voltage [LINE_3] = 250;
}

static void publish_sensor_data(sensor_id_t sensor_id)
{
     float value_1, value_2, value_3;
     value_1 = input_voltage [LINE_1];
     value_2 = input_voltage [LINE_2];
     value_3 = input_voltage [LINE_3];
     webserver_get_data(value_1, value_2, value_3);
}
static active_line_t check_active_line()
{
       return webserver_get_active_line();;
}

static void set_active_line(active_line_t active_line )
{
        switch (active_line)
        {
        case ACTIVE_LINE_1:
             led_on(LINE_1_LED_PIN);
             led_off(LINE_2_LED_PIN);
             led_off(LINE_3_LED_PIN);
             //message_println("[LINE 1 ACTIVE]");
        break;

        case ACTIVE_LINE_2:
             led_off(LINE_1_LED_PIN);
             led_on(LINE_2_LED_PIN);
             led_off(LINE_3_LED_PIN);
             
        break;

        case ACTIVE_LINE_3:
             led_off(LINE_1_LED_PIN);
             led_off(LINE_2_LED_PIN);
             led_on(LINE_3_LED_PIN);
             
        break;

        case LINE_1_INACTIVE:
             led_off(LINE_1_LED_PIN);
             
        break;

        case LINE_2_INACTIVE:
             led_off(LINE_2_LED_PIN);
             
        break;

        case LINE_3_INACTIVE:
             led_off(LINE_3_LED_PIN);
             
        break;
        
        default:
             led_off(LINE_1_LED_PIN);
             led_off(LINE_2_LED_PIN);
             led_off(LINE_3_LED_PIN);
             
        break;
        }
}
void run_phase_selector_app(){
     read_sensor(SENSOR_AC_VOLTAGE);
     publish_sensor_data(SENSOR_AC_VOLTAGE);
     active_line_t active_line = check_active_line();
     set_active_line(active_line);
}