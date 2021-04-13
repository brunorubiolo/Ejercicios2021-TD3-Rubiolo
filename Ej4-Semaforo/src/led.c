#include "../include/led.h"


void configurarLed() // gpio_int_type_t ledRojo, gpio_int_type_t ledAmarillo, gpio_int_type_t ledVerde
// agegarle el argumento a la funcion asi puedo configurar los pines yo
{
    gpio_pad_select_gpio(Rojo);
    gpio_set_direction(Rojo, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(Amarillo);
    gpio_set_direction(Amarillo, GPIO_MODE_OUTPUT);
     gpio_pad_select_gpio(Verde);
    gpio_set_direction(Verde, GPIO_MODE_OUTPUT);
}

void prenderLed(gpio_int_type_t led)
{
gpio_set_level(led,1);
}

void apagarLed(gpio_int_type_t led)
{
gpio_set_level(led,0);
}