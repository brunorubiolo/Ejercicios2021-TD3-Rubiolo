#ifndef LED_H_
#define LED_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

extern int contador;

extern portMUX_TYPE mux; //Inicializa el spinlock desbloqueado

void iniciar_LedA( void );

void iniciar_LedB( void );

#endif