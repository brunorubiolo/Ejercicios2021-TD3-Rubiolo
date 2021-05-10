#include "../include/led.h"


#define LED1 GPIO_NUM_6 
#define LED2 GPIO_NUM_7
#define LED3 GPIO_NUM_8


/ Tipo de datos para la variable de estados
typedef enum{
    ESTADO_INICIAL, // Sin ningun pulsador activado
    ESTADO_1,       //pulsador 1 activado
    ESTADO_2,       //pulsador 2 activado
} estadoMEF_t;

// Variable de estado (global)
estadoMEF_t estadoActual;

void iniciarLed() 

{
    gpio_pad_select_gpio(LED1);
	gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED2);
	gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED3);
	gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
}

void InicializarMEF(void){
	 estadoActual = ESTADO_INICIAL;

}

void actualizarLed(){


switch (estadoActual) {
		case ESTADO_INICIAL:
        {   //apago todos los led
            //estado inicial es sin un pulsador activado y todos los led apagados
            gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 0);

			if(gpio_get_level(PUL1) == TRUE){
				// Cambiar a otro estado
				 estadoActual = ESTADO_1; //si pulsador 1 se activa paso a estado 1
			}
            if(gpio_get_level(PUL2) == TRUE){
				// Cambiar a otro estado
				 estadoActual = ESTADO_2; //si pulsador 1 se activa paso a estado 2
			}
		}
		break;
		case ESTADO_1:{

			gpio_set_level(LED1, 1);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 0);
            vTaskDelay(T_ON);
            gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 1);
			gpio_set_level(LED3, 0);
            vTaskDelay(T_ON);
            gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 1);
            vTaskDelay(T_ON);
		}
		break;
		case ESTADO_2:{
			
            gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 1);
            vTaskDelay(T_ON);
            gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 1);
			gpio_set_level(LED3, 0);
            vTaskDelay(T_ON);
            gpio_set_level(LED1, 1);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 0);
            vTaskDelay(T_ON);

		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
			InicializarMEF();
		}
		break;
	}	



}