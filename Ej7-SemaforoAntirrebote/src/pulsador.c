#include "../include/pulsador.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define T_ESPERA 10 //cantidad de veces que va a ingresar antes de cambiar de estado
#define pulsador GPIO_NUM_18

estadoBoton_t estadoPulsador;

int cambioModo = 0;

void iniciarPulsador()
{
    estadoPulsador = BAJO;  // Se configura estado inicial
    gpio_pad_select_gpio(pulsador);
    gpio_set_direction(pulsador, GPIO_MODE_INPUT); //Configura el pin como entrada digital
    gpio_set_pull_mode(pulsador, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna

}



//Actualización de la MEF
void actualizarPulsador()
{
   static uint8_t contDescendente = 0;
   static uint8_t contAscendente = 0;

   switch( estadoPulsador ){

      case BAJO: 
         if( gpio_get_level(pulsador) ){
            estadoPulsador = ASCENDENTE;
         }
      break;

      case ASCENDENTE:      
         if( contAscendente >= T_ESPERA ){
            if( gpio_get_level(pulsador) ){
               estadoPulsador = ALTO;
               } else{
               estadoPulsador = BAJO;
            }
            contAscendente = 0;
         }
         contAscendente++;
      break;

      case ALTO:
         if( !gpio_get_level(pulsador) ){
            estadoPulsador = DESCENDENTE;
         }
      break;

      case DESCENDENTE:      
         if( contDescendente >= T_ESPERA ){
            if( !gpio_get_level(pulsador) ){
               estadoPulsador = BAJO;
               pulsadorLiberado();
            } else{
               estadoPulsador = ALTO;
            }
            contDescendente = 0;
         }
         contDescendente++;
      break;

      default:
         estadoPulsador = BAJO;
      break;
   }
}


void pulsadorLiberado( void )
{
    cambioModo = !cambioModo;
}