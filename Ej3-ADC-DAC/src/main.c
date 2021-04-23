// programa de control de un Led

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h>
#include <driver/dac.h>


void app_main() {
    //configuro el adc1
    adc1_config_width(ADC_WIDTH_12Bit); //configuran la resoluncion 
    adc1_config_channel_atten (ADC1_CHANNEL_0 ,ADC_ATTEN_DB_0);
   
   //configuro el adc2
    adc2_config_channel_atten (ADC2_CHANNEL_0, ADC_ATTEN_DB_0);
    
    //configuro el conversor digital analogico
    dac_output_enable(DAC_CHANNEL_1);

//BUCLE

    while(true)
    {
        int ValorAdc = adc1_get_raw(ADC1_CHANNEL_0); // Leo el valor del ADC1
        printf("El valor del ADC1 es %d\n",ValorAdc); // Escribo en serial el valor del adc


        //El dac es de 8 bit
        //pongo en la salida el valor del adc
        dac_output_voltage(DAC_CHANNEL_1,(ValorAdc*255/4095)); 


        vTaskDelay(500/portTICK_PERIOD_MS);        
    }



}
