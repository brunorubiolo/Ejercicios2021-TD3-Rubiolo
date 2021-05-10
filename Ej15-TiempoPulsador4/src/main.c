/*=============================================================================
 * Author: Bruno Rubiolo.
 * Date: 10/05/2021 
 * Board: ESP32
 * 
 *      La tarea Pulsador se realiza en el procesador
 *      La tarea led tambien la realizo en el procesador porque queria probar en vez del coprocesador
 *      La tarea Pulsador tiene mayor prioridad frente a la tarea led
 * 
 *      Inicio solo la tarea pulsador, Una vez que el boton es liberado, llamo a una funcion Encender_Led
 *     la que me crea la nueva tarea led, la ejecuto al mismo tiempo que la otra, con un delay bloquante.
 *     Una vez finalizada la destruyo.
 * 
 *===========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"
#include "led.h"


#define T_ESPERA_MS  40
#define T_ESPERA     pdMS_TO_TICKS(T_ESPERA_MS)
#define PROCESADORA 0
#define PROCESADORB 1

void tareaDestello( void* taskParmPtr ); //Prototipo de la función de la tarea

void app_main()
{

    inicializarPulsador();
    Iniciar_Led();


}

