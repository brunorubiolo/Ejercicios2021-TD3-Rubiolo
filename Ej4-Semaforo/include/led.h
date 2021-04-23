#ifndef LED_H //  controla que otro archivo no haya llamado a led.h
#define LED_H
#include "driver/gpio.h"



void configurarLed(gpio_int_type_t ledRojo, gpio_int_type_t ledAmarillo, gpio_int_type_t ledVerde); //gpio_int_type_t ledRojo, gpio_int_type_t ledAmarillo, gpio_int_type_t ledVerde
void prenderLed(gpio_int_type_t led);
void apagarLed(gpio_int_type_t led);

#endif