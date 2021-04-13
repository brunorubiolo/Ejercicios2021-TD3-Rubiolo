#ifndef LED_H // 
#define LED_H
#include "driver/gpio.h"

#define Verde GPIO_NUM_25
#define Amarillo GPIO_NUM_32
#define Rojo GPIO_NUM_26

void configurarLed(); //gpio_int_type_t ledRojo, gpio_int_type_t ledAmarillo, gpio_int_type_t ledVerde

void prenderLed(gpio_int_type_t led);
void apagarLed(gpio_int_type_t led);

#endif