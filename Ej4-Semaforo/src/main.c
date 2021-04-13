#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/led.h"


void app_main() {

    //funcion configurar led
    configurarLed(); //le mando los pines de conexion de leds
    //funcion iniciar semaforo
    iniciarSemaforo();
    

    while(1){
        //funcion actualizar semaforo
        actualizarSemaforo();

    }

}