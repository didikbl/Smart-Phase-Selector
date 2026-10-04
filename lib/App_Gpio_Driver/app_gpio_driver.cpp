#include "app_gpio_driver.h"
#include "app_types.h"


void gpio_init_outpout_pin(gpio_pin_t pin){
     pinMode(pin, OUTPUT);
}
void gpio_init_input_pin(gpio_pin_t pin){
     pinMode(pin, INPUT);
}
void gpio_read_pin(gpio_pin_t pin){
     digitalRead(pin);
}
void gpio_write_pin(gpio_pin_t pin, uint8_t state){
     digitalWrite(pin, state);
}