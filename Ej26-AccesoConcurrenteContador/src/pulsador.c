/*==================[ Inclusiones ]============================================*/
#include "pulsador.h"

/*==================[ Definiciones ]===================================*/

#define T_REBOTE_MS   40
#define T_REBOTE pdMS_TO_TICKS(T_REBOTE_MS)
#define SALIDA_PRUEBA   GPIO_NUM_26
#define PROCESADORA 0
#define PROCESADORB 1

/*==================[Prototipos de funciones]======================*/

//static void errorPulsador( void );
//static void botonPresionado( void );
//static void botonLiberado( void );

void tareaPulsador( void* taskParmPtr );

/*==================[Variables]==============================*/
gpio_int_type_t pulsadorPines[2] = { GPIO_NUM_18, GPIO_NUM_19 };

pulsadorInfo pulsador[2];

int contador = 100;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED; //Inicializa el spinlock desbloqueado

/*==================[Implementaciones]=================================*/




void inicializarPulsador( void )
{
    for(uint8_t i = 0; i < 2; i++){
        pulsador[i].tecla             = pulsadorPines[i];
        pulsador[i].estado            = ALTO;                     //Estado inicial
        pulsador[i].tiempoBajo        = TIEMPO_NO_VALIDO;
        pulsador[i].tiempoAlto        = TIEMPO_NO_VALIDO;
        pulsador[i].diferenciaTiempo  = TIEMPO_NO_VALIDO;

        gpio_pad_select_gpio(pulsador[i].tecla);
        gpio_set_direction(pulsador[i].tecla , GPIO_MODE_INPUT);
        gpio_set_pull_mode(pulsador[i].tecla, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna

        gpio_pad_select_gpio(SALIDA_PRUEBA);                //replica lo que hace el pulsador
        gpio_set_direction(SALIDA_PRUEBA, GPIO_MODE_OUTPUT);
    }

    // Crear tareas en freeRTOS
    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaPulsador,                     	// Funcion de la tarea a ejecutar
        "tareaPulsador",   	                // Nombre de la tarea como String amigable para el usuario
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



// pulsador_ Update State Function
void actualizarPulsador()
{   for(uint8_t i = 0; i < 2; i++){

        switch( pulsador[i].estado )
        {
            case BAJO:
                if( gpio_get_level( pulsador[i].tecla ) ){
                    pulsador[i].estado = ASCENDENTE;
                }
                break;

            case ASCENDENTE:                                     // ACA SE ME PRODUCE EL CONFLICTO
                if( gpio_get_level( pulsador[i].tecla ) ){
                    portENTER_CRITICAL(&mux);
                    if(pulsador[0].estado== ASCENDENTE){
                    //gpio_set_level( SALIDA_PRUEBA, 0 );         //para tener una referencia en el debug
                        if(contador<900){
                            contador=contador+100;
                        } else{
                            contador = 900;
                        }
                    }                    
                    if(pulsador[1].estado== ASCENDENTE){
                    //gpio_set_level( SALIDA_PRUEBA, 1 );         //para tener una referencia en el debug
                        if(contador>100){
                            contador=contador-100;
                        } else{
                            contador = 100;
                        }
                    
                    }
                    portEXIT_CRITICAL(&mux);
                    pulsador[i].estado = ALTO;
                    
                }
                else{
                    pulsador[i].estado = BAJO;
                }
                break;

            case ALTO:
                if( !gpio_get_level( pulsador[i].tecla ) ){
                    pulsador[i].estado = DESCENDENTE;
                }
                break;

            case DESCENDENTE:
                if( !gpio_get_level( pulsador[i].tecla ) ){
                    pulsador[i].estado = BAJO;
                   // botonLiberado();
                }
                else{
                    pulsador[i].estado = ALTO;
                }
                break;

            default:
                pulsador[i].estado = ALTO;
                break;
        }
    }
}

/*
static void botonPresionado()
{
      gpio_set_level( SALIDA_PRUEBA, 1 );         //para tener una referencia en el debug
 }

static void botonLiberado()
{
  gpio_set_level( SALIDA_PRUEBA, 0 );         //para tener una referencia en el debug
 }
*/

void tareaPulsador( void* taskParmPtr )
{
    while( true )
    {
        actualizarPulsador();
        vTaskDelay( T_REBOTE );
    }
}