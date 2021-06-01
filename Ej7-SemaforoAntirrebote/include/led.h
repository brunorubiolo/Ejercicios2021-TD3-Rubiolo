#ifndef LED_H_ //  controla que otro archivo no haya llamado a led.h
#define LED_H_

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void configurarLed(); 
void prenderLed(gpio_int_type_t led);
void apagarLed(gpio_int_type_t led);


#endif