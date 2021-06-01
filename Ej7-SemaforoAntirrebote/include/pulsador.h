#ifndef PULSADOR_H
#define PULSADOR_H

#include "driver/gpio.h"

typedef enum{
   ALTO,
   BAJO,
   DESCENDENTE,
   ASCENDENTE
} estadoBoton_t;

void iniciarPulsador( void );
void actualizarPulsador( void );
void pulsadorLiberado( void );

#endif