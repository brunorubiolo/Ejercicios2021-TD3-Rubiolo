#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/led.h"
#include "../include/pulsador.h"


void app_main() {


    //funcion iniciar led
    iniciarLed();
    //funcion iniciar pulsadores
    iniciarPulsador();
    //funcion iniciar MEF
    InicializarMEF();

    while(1){
        //funcion actualizar leds
        actualizarLed();

    }

}