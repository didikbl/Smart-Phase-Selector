#ifndef M_GPIO_DRIVER_H
#define M_GPIO_DRIVER_H
#include <Arduino.h>
#include "app_types.h"


//--------------DRIVER LAYER------------------------
void gpio_init_outpout_pin(gpio_pin_t pin);
void gpio_init_input_pin(gpio_pin_t pin);
void gpio_read_pin(gpio_pin_t pin);
void gpio_write_pin(gpio_pin_t pin, uint8_t state);

#endif