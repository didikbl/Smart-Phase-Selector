#include "app_actuators.h"


void relay_on(gpio_pin_t pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_ON);
}
void relay_off(gpio_pin_t pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_OFF);
}
void led_on(gpio_pin_t  pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_ON);
}
void led_off(gpio_pin_t  pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_OFF);
}
void led_blink(gpio_pin_t  pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_ON);
     vTaskDelay(pdMS_TO_TICKS(1000));
     gpio_write_pin(pin, ACTUATOR_OFF);
     vTaskDelay(pdMS_TO_TICKS(1000));
}
void buzzer_on(gpio_pin_t pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_ON);
}
void buzzer_off(gpio_pin_t pin){
     gpio_init_outpout_pin(pin);
     gpio_write_pin(pin, ACTUATOR_OFF);
}