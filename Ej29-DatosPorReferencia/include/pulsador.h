#ifndef PULSADOR_H_
#define PULSADOR_H_
/*==================[ Inclusiones ]============================================*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "freertos/semphr.h" //incluyo la libreria del semaforo
/*==================[ Definiciones ]===================================*/
#define TIEMPO_NO_VALIDO   0
#define N_PULSADOR      3                           //Cantidad de pulsadores

typedef enum
{
    ALTO,
    BAJO,
    DESCENDENTE,
    ASCENDENTE
} estadoPulsador;

typedef struct
{
    gpio_int_type_t tecla;
    estadoPulsador estado;   //variables
    TickType_t tiempoBajo;		//tiempo de la última transición del estado alto a bajo
    TickType_t tiempoAlto;		    //tiempo de la última transición del estado bajo a alto
    TickType_t diferenciaTiempo;	    //variables
    //QueueHandle_t cola;
} pulsadorInfo;


// Estructura para la cola
typedef struct
{
    uint8_t indice_de_led;		
    TickType_t tiempo_medido;	// Tipo ticktype porq mando el tiempo medido en tick	
} estructuraLed;



/*==================[Prototipos de funciones]======================*/
void inicializarPulsador(  void );
TickType_t obtenerDiferencia( uint8_t  indice);
void borrarDiferencia( uint8_t  indice );

#endif