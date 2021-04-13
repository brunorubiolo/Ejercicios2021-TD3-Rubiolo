#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"


#define T_MS		10/portTICK_PERIOD_MS

// DECLARACION DE ENTRADAS, SALIDAS Y CONTADORES
int led1 = GPIO_NUM_32;
int led2 = GPIO_NUM_33;
int pulsador1 = GPIO_NUM_26;
int pulsador2 = GPIO_NUM_27;
unsigned long int contador1 = 0; 
unsigned long int contador2 = 0;

void app_main() {

        //LED1 Y LED2 COMO SALIDA DIGITAL
        gpio_pad_select_gpio(led1); 
		gpio_set_direction(led1], GPIO_MODE_OUTPUT); 
	    gpio_pad_select_gpio(led2); 
		gpio_set_direction(led2, GPIO_MODE_OUTPUT); 
	
        //PULSADOR1 Y PULSADOR2 COMO ENTRADA DIGITAL
        gpio_pad_select_gpio(pulsador1); 
		gpio_set_direction(pulsador1], GPIO_MODE_OUTPUT); 
	    gpio_pad_select_gpio(pulsador2); 
		gpio_set_direction(pulsador2, GPIO_MODE_OUTPUT); 

   //BUCLE

   while( true )
    {
		while (gpio_get_level(pulsador1) == 1)
		{
			vTaskDelay(T_MS);
			contador1 += T_MS;
		}
	   	while (gpio_get_level(pulsador2) == 1)
		{
			vTaskDelay(T_MS);
			contador2 += T_MS;
		}	

		
	   	if (contador1 >0)
		{
			gpio_set_level(led1, 1);
			vTaskDelay(contador1);
			gpio_set_level(led1, 0);
            contador1 = 0;
		}
	   	if (contador2 >0)
		{
			gpio_set_level(led2, 1);
			vTaskDelay(contador2);
			gpio_set_level(led2, 0);
            contador2 = 0;
		}
	}



}