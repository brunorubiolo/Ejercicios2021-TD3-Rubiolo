#include "led.h"
#include "pulsador.h"
#include "freertos/semphr.h"

#define SALIDA1     GPIO_NUM_25 // pin de Led Verde
#define SALIDA2     GPIO_NUM_27 // pin led Rojo
#define LED_ON_MS    500
#define LED_ON       pdMS_TO_TICKS(LED_ON_MS)
#define PERIODO_MS  1000
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)

extern SemaphoreHandle_t semaforo;

void tareaLed( void* taskParmPtr );

void Iniciar_Led(){
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1 , GPIO_MODE_OUTPUT);
    gpio_set_level(SALIDA1, 0); // Lo inicio apagado
    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2 , GPIO_MODE_OUTPUT);
    gpio_set_level(SALIDA2, 0); // Lo inicio apagado

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaLed,                     	// Funcion de la tarea a ejecutar
        "tareaLed",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        1                                   //CO Procesador
    );

    // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}

}


void tareaLed( void* taskParmPtr )
    {   
        while (true){

        TickType_t xPeriodicity =  PERIODO;			// Tarea periodica cada 1000 ms

        TickType_t xLastWakeTime = xTaskGetTickCount();

        
        if(xSemaphoreTake( semaforo, pdMS_TO_TICKS(10) ) == pdTRUE){
            
            gpio_set_level( SALIDA2, 0 );
            gpio_set_level( SALIDA1, 1 );
            vTaskDelay( LED_ON );
            gpio_set_level( SALIDA1, 0 );
        }
        else {
            gpio_set_level( SALIDA1, 0 );
            gpio_set_level( SALIDA2, 1 );
            vTaskDelay( LED_ON );
            gpio_set_level( SALIDA2, 0 );

        }
            
        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
        }
        
    }