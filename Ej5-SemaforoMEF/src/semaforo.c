#include "../include/led.h"
#include "../include/semaforo.h"
#include "freertos/task.h"

//establezco los pines para los led en un define para poder cambiarlos mas facil si es necesario
#define VERDE GPIO_NUM_25
#define AMARILLO GPIO_NUM_26
#define ROJO GPIO_NUM_27

//Establezco los tipos de datos para la MEF
typedef enum{
    ROJO,
    ROJO_AMARILLO,
    VERDE,
    AMARILLO
} estadoMEF_t;

estadoMEF_t estadoActual, estadoAnterior; // Variable de estado (global)

int contador; //variable para contar la cantidad de veces que ingresa a la funcipon actualizar MEF

// Función Inicializar MEF
void iniciarSemaforo(void){
	configurarLed(ROJO, AMARILLO, VERDE);
	estadoActual = ROJO;
	estadoAnterior = AMARILLO;
	contador = 0;
}

// Función Actualizar MEF
void actualizarSemaforo(void)
{
	switch (estadoActual) {
		case ROJO:
        {
            // Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				prenderLed(ROJO);
				apagarLed(AMARILLO);
				apagarLed(VERDE);
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == 500 ){
				// Cambiar a otro estado
				 estadoActual = ROJO_AMARILLO;
				 contador = 0;
			}
			contador++;
		}
		break;
		case ROJO_AMARILLO:{
			// Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				prenderLed(ROJO);
				prenderLed(AMARILLO);
				apagarLed(VERDE);
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == 100 ){
				// Cambiar a otro estado
				 estadoActual = VERDE;
				 contador = 0;
			}
			contador++;
		}
		break;
		case VERDE:{
			// Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				apagarLed(ROJO);
				apagarLed(AMARILLO);
				prenderLed(VERDE);
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == 300 ){
				// Cambiar a otro estado
				 estadoActual = AMARILLO;
				 contador = 0;
			}
			contador++;
		}
		break;
		case AMARILLO:{
			// Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				apagarLed(ROJO);
				prenderLed(AMARILLO);
				apagarLed(VERDE);
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == 100 ){
				// Cambiar a otro estado
				 estadoActual = ROJO;
				 contador = 0;
			}
			contador++;
		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
			iniciarSemaforo();
		}
		break;
	}	
}