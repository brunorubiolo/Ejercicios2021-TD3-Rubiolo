/*=============================================================================
 * Author: Bruno Rubiolo.
 * Date: 31/05/2021 
 * Board: ESP32
 * 
 *      La tarea Pulsador se realiza en el procesador (TAREA A)
 *      La tarea ledA se realiza en el co procesador (TAREA B)
 *      La tarea ledB se realiza en el co procesador (TAREA C)
 * 
 *      PULSADOR1 -> G18
 *      PULSADOR2 -> G19
 *      LED1      -> G25
 *      LED2      -> G16
 * 
 *      Adjunto imagenes del osciloscopio
 *              CANAL 1 LED B
 *              CANAL 2 LED A 
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


void app_main()
{
    inicializarPulsador();  // TAREA A
    iniciar_LedA();         // TAREA B
    iniciar_LedB();         // TAREA C
}