/*=============================================================================
 * Author: Bruno Rubiolo.
 * Date: 07/06/2021 
 * Board: ESP32
 * 
 *      La tarea Destello se realiza en el procesador (TAREA B)
 *      La tarea Pulsador se realiza en el co procesador (TAREA A)
 * 
 *      PULSADOR -> G18
 *      LED      -> G25
 * 
 *===========================================================================*/


#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25
#define PERIODO_MS  1000
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)
#define PROCESADORA 0
#define PROCESADORB 1
#define N_LED       1

gpio_int_type_t led [N_PULSADOR] = {GPIO_NUM_25};



extern QueueHandle_t cola;

extern pulsadorInfo pulsadorA;

void tareaDestello( void* taskParmPtr ); //Prototipo de la función de la tarea

void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    inicializarPulsador();

    //Creacion de la tarea destello

    BaseType_t res = xTaskCreatePinnedToCore(
            tareaDestello,                     	// Funcion de la tarea a ejecutar
            "tareaDestello",   	                // Nombre de la tarea como String amigable para el usuario
            configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
            NULL,                          	// Parametros de tarea
            tskIDLE_PRIORITY,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
            NULL,                          		// Puntero a la tarea creada en el sistema
            PROCESADORA
        );
    // Gestion de errores
    if(res == pdFAIL)
    {
        printf( "Error al crear la tarea.\r\n" );
        while(true);					// si no pudo crear la tarea queda en un bucle infinito
    }
}

// Implementacion de funcion de la tarea
void tareaDestello( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    
    gpio_pad_select_gpio(led[0]);
    gpio_set_direction(led[0], GPIO_MODE_OUTPUT);

    TickType_t xPeriodicity =  PERIODO;
	TickType_t xLastWakeTime = xTaskGetTickCount();

    TickType_t dif = 0;
    uint8_t IndiceDelLed = 0;


    estructuraLed* punteroEstructura;   // Creo un puntero donde voy a recibir el dato

    // ---------- Bucle infinito --------------------------
    while( true )
    {                   //          
        if(xQueueReceive( cola , &punteroEstructura,  0 )) //recibo dato desde la cola sin tiempo de espera
        {
            dif = punteroEstructura-> tiempo_medido;
            IndiceDelLed = punteroEstructura -> indice_de_led;
            //acá se recibió
            if( dif > xPeriodicity )        // Si la diferencia es mayor al periodo lo hago igual al periodo
            {
                dif = xPeriodicity;
            }
        }
        else
        {
            //acá no se recibió
        }
         
        gpio_set_level( led[IndiceDelLed], 1 );
        vTaskDelay( dif );
        gpio_set_level( led[IndiceDelLed], 0 );

        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
    }
}