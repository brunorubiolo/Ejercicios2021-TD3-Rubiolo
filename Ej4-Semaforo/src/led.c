#include "../include/led.h"

//estas variables solamente son accesibles en este archivo
static gpio_int_type_t ledRojo, ledAmarillo, ledVerde; 


void configurarLed(gpio_int_type_t ledRojo, gpio_int_type_t ledAmarillo, gpio_int_type_t ledVerde) // gpio_int_type_t ledRojo, gpio_int_type_t ledAmarillo, gpio_int_type_t ledVerde
// agegarle el argumento a la funcion asi puedo configurar los pines yo
{
    gpio_pad_select_gpio(ledRojo);
    gpio_set_direction(ledRojo, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(ledAmarillo);
    gpio_set_direction(ledAmarillo, GPIO_MODE_OUTPUT);
     gpio_pad_select_gpio(ledVerde);
    gpio_set_direction(ledVerde, GPIO_MODE_OUTPUT);
}

void prenderLed(gpio_int_type_t led)
{
gpio_set_level(led,1);
}

void apagarLed(gpio_int_type_t led)
{
gpio_set_level(led,0);
}