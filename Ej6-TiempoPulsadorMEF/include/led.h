#ifndef LED_H //  controla que otro archivo no haya llamado a led.h
#define LED_H
#include "driver/gpio.h"

void iniciarLed(); 
void actualizarLed();
void InicializarMEF();


#endif