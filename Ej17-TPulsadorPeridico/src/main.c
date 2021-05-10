/*=============================================================================
 * Author: Bruno Rubiolo.
 * Date: 10/05/2021 
 * Board: ESP32
 * 
 *      La tarea Pulsador se realiza en el procesador
 *      La tarea led se realiza en el co-procesador
 * 
 *      Las dos tareas se ejecutan al mismo tiempo. La tarea led enciende el led 
 *     cada un periodo de 1000 ms con un ciclo util igual al tiempo que mantengamos 
 *     el pulsador apretado. Luego de apagarlo en ese tiempo, pongo la tarea en 
 *     estado bloqueado para que se complete el periodo.
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

#define SALIDA1     GPIO_NUM_25
#define T_ESPERA_MS  40
#define T_ESPERA     pdMS_TO_TICKS(T_ESPERA_MS)
#define PROCESADORA 0
#define PROCESADORB 1



void app_main()
{

    inicializarPulsador();

    iniciar_Led();

}

