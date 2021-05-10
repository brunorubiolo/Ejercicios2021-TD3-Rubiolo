#include "led.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25 // pin de Led

void tareaLed( void* taskParmPtr );

void Iniciar_Led(){
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1 , GPIO_MODE_OUTPUT);
    gpio_set_level(SALIDA1, 0); // Lo inicio apagado
}

void Encender_Led(){

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaLed,                     	// Funcion de la tarea a ejecutar
        "tareaLed",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        0                                   //Procesador
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
        int dif = obtenerDiferencia();

        while( true )
        {
            gpio_set_level( SALIDA1, 1 );
            vTaskDelay( dif );
            gpio_set_level( SALIDA1, 0 );
            borrarDiferencia();

            vTaskDelete(NULL); // Borro la tarea!!
        }
    }