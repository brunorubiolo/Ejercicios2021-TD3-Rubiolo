

#include "../driver/include/driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED1 GPIO_NUM_6 //ver de crear un tipo de datos
#define LED2 GPIO_NUM_7
#define LED3 GPIO_NUM_8
#define PUL1 GPIO_NUM_36
#define PUL2 GPIO_NUM_39
#define T_ON		500/portTICK_PERIOD_MS

void app_main() {

gpio_pad_select_gpio(LED1);
	gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED2);
	gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED3);
	gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(PUL1);
	gpio_set_direction(PUL1, GPIO_MODE_INPUT);
	gpio_pad_select_gpio(PUL2);
	gpio_set_direction(PUL2, GPIO_MODE_INPUT);

     while( true )
    {
		int sentido = 0;

	   	if (gpio_get_level(PUL1) == 0)
		{
			sentido = 1;
		}
	   	else if (gpio_get_level(PUL2) == 0)
		{
			sentido = 0;
		} else {
            gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 1);
			gpio_set_level(LED3, 0);
        }

		if(sentido == 0){
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
		if(sentido == 1){
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
		
	}
   return 0;
}