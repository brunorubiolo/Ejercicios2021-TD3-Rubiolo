#include "../include/led.h"
#include "../include/semaforo.h"
#include "freertos/task.h"

//establezco los pines para los led en un define para poder cambiarlos mas facil si es necesario
#define VERDEs GPIO_NUM_25
#define AMARILLOs GPIO_NUM_26
#define ROJOs GPIO_NUM_27

//Establezco los tipos de datos para la MEF
typedef enum{
    ROJO,
    ROJO_AMARILLO,
    VERDE,
    AMARILLO,

	intermitente1,
	intermitente2

} estadoMEF_t;

estadoMEF_t estadoActual, estadoAnterior, estadoActualIntermitente, estadoAnteriorIntermitente; // Variable de estado (global)

int contador, contadorIntermitente; //variable para contar la cantidad de veces que ingresa a la funcipon actualizar MEF

// Función Inicializar MEF
void iniciarSemaforo(void){
	configurarLed();
	estadoActual = ROJO;
	estadoAnterior = AMARILLO;
	contador = 0;
}

void iniciarSemaforoIntermitente(void){
	estadoActualIntermitente = intermitente1;
	estadoAnteriorIntermitente = intermitente2;
	contadorIntermitente=0;
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
				prenderLed(ROJOs);
				apagarLed(AMARILLOs);
				apagarLed(VERDEs);
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
				prenderLed(ROJOs);
				prenderLed(AMARILLOs);
				apagarLed(VERDEs);
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
				apagarLed(ROJOs);
				apagarLed(AMARILLOs);
				prenderLed(VERDEs);
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
				apagarLed(ROJOs);
				prenderLed(AMARILLOs);
				apagarLed(VERDEs);
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

void actualizarIntermitente(void)
{
	switch (estadoActualIntermitente) {
		case intermitente1:{
			// Actualizar salida del estado
			if(estadoAnteriorIntermitente != estadoActualIntermitente)
			{
				apagarLed(ROJOs);
				prenderLed(AMARILLOs);
				apagarLed(VERDEs);
				estadoAnteriorIntermitente = estadoActualIntermitente;
			}
    		// Chequear condiciones de transición de estado
			if(contadorIntermitente == 100 ){
				// Cambiar a otro estado
				 estadoActualIntermitente = intermitente2;
				 contadorIntermitente = 0;
			}
			contadorIntermitente++;
		}
		break;
		case intermitente2:{
			// Actualizar salida del estado
			if(estadoAnteriorIntermitente != estadoActualIntermitente)
			{
				apagarLed(ROJOs);
				apagarLed(AMARILLOs);
				apagarLed(VERDEs);
				estadoAnteriorIntermitente = estadoActualIntermitente;
			}
    		// Chequear condiciones de transición de estado
			if(contadorIntermitente == 100 ){
				// Cambiar a otro estado
				 estadoActualIntermitente = intermitente1;
				 contadorIntermitente = 0;
			}
			contadorIntermitente++;
		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
		}
		break;
	}	
}