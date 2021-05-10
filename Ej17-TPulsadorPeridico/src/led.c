#include "led.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25 // pin de Led
#define PROCESADORA 0
#define PROCESADORB 1
#define PERIODO_MS  1000
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)
#define MAX_INC     (PERIODO_MS - dif)

void tareaLed( void* taskParmPtr );

void iniciar_Led(){
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1 , GPIO_MODE_OUTPUT);
    gpio_set_level(SALIDA1, 0); // Lo inicio apagado

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaLed,                     	// Funcion de la tarea a ejecutar
        "tareaLed",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORB
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
        TickType_t xPeriodicity =  PERIODO;			// Tarea periodica cada 1000 ms

        TickType_t xLastWakeTime = xTaskGetTickCount();

        while( true )
        {  
        int dif = obtenerDiferencia();
        gpio_set_level(SALIDA1, 1);
        vTaskDelay ( pdMS_TO_TICKS(dif) );
        gpio_set_level(SALIDA1, 0);

        if ( dif == MAX_INC )
        {
            dif = 0;
        }

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );

        }
    }
