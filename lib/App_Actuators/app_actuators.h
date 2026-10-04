#ifndef ACTUATOR_H
#define ACTUATOR_H
#include "app_gpio_driver.h"
#include "app_types.h"


//--------------HARDWARE ABSTRACTION LAYER----------
//-----------------------FOR RELAYS----------------------------------
void relay_on(gpio_pin_t pin);
void relay_off(gpio_pin_t pin);

//--------------------------FOR LEDs------------------------------------
void led_on(gpio_pin_t pin);
void led_off(gpio_pin_t pin);
void led_blink(gpio_pin_t pin);
//--------------------------FOR BUZZERs------------------------------------
void buzzer_on(gpio_pin_t pin);
void buzzer_off(gpio_pin_t pin);

/*--------------HARDWARE ABSTRACTION LAYER GENERIC API----------
void actuator_set(gpio_pin_t pin, actuator_state_t state);
void actuator_set(gpio_pin_t pin, actuator_state_t state, int frequency, int duty_cycle);*/



#endif