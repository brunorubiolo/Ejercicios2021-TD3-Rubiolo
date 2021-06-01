#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/*=============================================================================
 * Author: Bruno Rubiolo.
 * Date: 1/06/2021 
 * Board: ESP32
 * 
 *      Led verde -> G25
 *      Led amarillo -> G26
 *      Led verde -> G27
 *      Pulsador -> G18
 * 
 *      Adjunto imagenes del funcionamiento
 *          Canal 1 led verde
 *          Canal 2 led amarillo
 *        En una imagen se ve el funcionamiento normal y en la otra el intermitente
 * 
 *===========================================================================*/

#include "../include/semaforo.h"
#include "../include/led.h"
#include "../include/pulsador.h"

extern int cambioModo;

void app_main() {

    iniciarSemaforo();
    iniciarSemaforoIntermitente();
    iniciarPulsador();

    while(1){
        
        actualizarPulsador();

        if(cambioModo == 0){
            actualizarSemaforo();
        }
        else{
            actualizarIntermitente();
        }
    }
}