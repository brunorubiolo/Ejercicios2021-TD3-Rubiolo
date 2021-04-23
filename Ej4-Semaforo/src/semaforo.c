#include "../include/led.h"
#include "../include/semaforo.h"
#include "freertos/task.h"

//establezco los pines para los led en un define para poder cambiarlos mas facil si es necesario
#define VERDE GPIO_NUM_25
#define AMARILLO GPIO_NUM_26
#define ROJO GPIO_NUM_27


//funcion iniciarSemaforo
void iniciarSemaforo(){
    //llamo a la funcion configurar led
    //le paso como argumento los pines donde estan conectados
    configurarLed(ROJO, AMARILLO, VERDE);
}

//funcion actualizarSemaforo
void actualizarSemaforo(){

    prenderLed(ROJO);
    vTaskDelay(30);
    prenderLed(AMARILLO);
    vTaskDelay(10);
    apagarLed(ROJO);
    apagarLed(AMARILLO);
    prenderLed(VERDE);
    vTaskDelay(10);
    apagarLed(VERDE);
    prenderLed(AMARILLO);
    vTaskDelay(5);
    apagarLed(AMARILLO);
}