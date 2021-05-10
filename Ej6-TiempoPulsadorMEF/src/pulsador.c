#include "../include/pulsador.h"


#define PUL1 GPIO_NUM_36
#define PUL2 GPIO_NUM_39


void iniciarPulsador() 

{
	gpio_pad_select_gpio(PUL1);
	gpio_set_direction(PUL1, GPIO_MODE_INPUT);
	gpio_pad_select_gpio(PUL2);
	gpio_set_direction(PUL2, GPIO_MODE_INPUT);
}
