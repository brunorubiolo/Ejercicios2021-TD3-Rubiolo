#include "../include/led.h"
#include "../include/semaforo.h"
#include "freertos/task.h"

void iniciarSemaforo(){

}

void actualizarSemaforo(){

    prenderLed(Rojo);
    vTaskDelay(30);
    prenderLed(Amarillo);
    vTaskDelay(10);
    apagarLed(Rojo);
    apagarLed(Amarillo);
    prenderLed(Verde);
    vTaskDelay(10);
    apagarLed(Verde);
    prenderLed(Amarillo);
    vTaskDelay(5);
    apagarLed(Amarillo);
}