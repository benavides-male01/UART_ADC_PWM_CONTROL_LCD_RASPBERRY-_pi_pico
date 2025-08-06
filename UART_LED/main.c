#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "funciones.h"
#include "hardware.h"

uint8_t porcentaje;
uint16_t pwm_level;
uint8_t valor_adc_remoto;

int main() {
    init();  // Inicializa UART, PWM, GPIO (según funciones.c)
         
    while (1) {

            // Esperamos a recibir un byte por UART
            if (uart_is_readable(UART_ID)) {
            valor_adc_remoto = uart_getc(UART_ID);
           
            //Convertimos de 0-255 a 0-4095 para usar en PWM
            pwm_level = valor_adc_remoto*16;//(valor_adc_remoto*16);

            // Seteamos el nivel de brillo del LED con PWM
            pwm_set_chan_level(slice, chan, pwm_level);

            // Calculamos porcentaje de brillo para enviar de vuelta
            porcentaje = (pwm_level * 100) / 4095;

            // Enviamos el porcentaje por UART al otro micro
            uart_putc(UART_ID, porcentaje);
        }
    }
}

