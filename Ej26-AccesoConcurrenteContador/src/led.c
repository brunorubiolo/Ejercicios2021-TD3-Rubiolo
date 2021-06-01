#include "led.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25 // pin de Led 1
#define SALIDA2     GPIO_NUM_16 // pin de led 2
#define PROCESADORA 0
#define PROCESADORB 1
#define PERIODO_MS  2000
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)

int valorcontador;

void tareaLedA( void* taskParmPtr );
void tareaLedB( void* taskParmPtr );

void iniciar_LedA(){

    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1 , GPIO_MODE_OUTPUT);
    

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaLedA,                     	// Funcion de la tarea a ejecutar
        "tareaLedA",   	                // Nombre de la tarea como String amigable para el usuario
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

void iniciar_LedB(){

    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2 , GPIO_MODE_OUTPUT);
    

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaLedB,                     	// Funcion de la tarea a ejecutar
        "tareaLedB",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
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

void tareaLedA( void* taskParmPtr )
    {  
        while( true )
        {   portENTER_CRITICAL(&mux);
            valorcontador=contador;      // LO GUARDO AL VALOR EN UNA VARIABLE LOCAL PARA NO TENER CONFLICTOS
            portEXIT_CRITICAL(&mux);
            gpio_set_level( SALIDA1, 1 );
            vTaskDelay((valorcontador/2)/ portTICK_PERIOD_MS);
            gpio_set_level( SALIDA1, 0 );
            vTaskDelay((valorcontador/2)/ portTICK_PERIOD_MS);
        }
    }


void tareaLedB( void* taskParmPtr )
    {  
        TickType_t xPeriodicity =  PERIODO;			// Tarea periodica cada 1000 ms

        TickType_t xLastWakeTime = xTaskGetTickCount();

        while( true )
        {  
            uint16_t duty = (contador*2);       // ACA SE ME PRODUCE EL CONFLICTO

            gpio_set_level( SALIDA2, 1 );
            vTaskDelay(pdMS_TO_TICKS(duty));
            gpio_set_level( SALIDA2, 0 );
            
            portENTER_CRITICAL(&mux);
            if(contador>100){                   // ACA SE ME PRODUCE EL CONFLICTO
                contador=contador-100;
            }else{
                contador=100;
            }
            portEXIT_CRITICAL(&mux);
            
            // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
            vTaskDelayUntil( &xLastWakeTime , xPeriodicity );

        }
    }