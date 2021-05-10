/*=============================================================================
 * Author: Bruno Rubiolo.
 * Date: 10/05/2021 
 * Board: ESP32
 * 
 *      La tarea Pulsador se realiza en el procesador
 *      La tarea led se realiza en el co procesador
 * 
 *      Adjunto imagenes del funcionamiento
 * 
 *===========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"   // agrego la libreria para semaforo
#include "pulsador.h"
#include "led.h"


#define T_ESPERA_MS  40
#define T_ESPERA     pdMS_TO_TICKS(T_ESPERA_MS)
#define PROCESADORA 0
#define PROCESADORB 1

SemaphoreHandle_t semaforo = NULL; //Puntero al semaforo



void app_main()
{
        //Crear el semáforo (arranca “tomado”)
    semaforo = xSemaphoreCreateBinary();
    if(semaforo == NULL)
    {
        printf("No se pudo crear el semaforo\n");
        while(true);
    }
    
    inicializarPulsador();
    Iniciar_Led();


}

