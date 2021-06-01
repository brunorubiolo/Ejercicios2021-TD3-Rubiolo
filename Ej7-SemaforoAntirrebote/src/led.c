#include "../include/led.h"

//estas variables solamente son accesibles en este archivo
//static gpio_int_type_t ledRojo, ledAmarillo, ledVerde; 


void configurarLed() 
{
    gpio_pad_select_gpio(GPIO_NUM_25);
    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(GPIO_NUM_26);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);
     gpio_pad_select_gpio(GPIO_NUM_27);
    gpio_set_direction(GPIO_NUM_27, GPIO_MODE_OUTPUT);
}

void prenderLed(gpio_int_type_t led)
{
gpio_set_level(led,1);
}

void apagarLed(gpio_int_type_t led)
{
gpio_set_level(led,0);
}