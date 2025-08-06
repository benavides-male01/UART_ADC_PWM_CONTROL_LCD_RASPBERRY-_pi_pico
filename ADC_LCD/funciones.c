#include <stdio.h>
#include "systick.h"
#include "hardware.h"

void init() {
    // Inicialización del ADC
    adc_init();
    adc_gpio_init(ADC_GPIO);
    adc_select_input(ADC_CHN);

    // Inicialización de la UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_pull_up(UART_RX_PIN);

    stdio_init_all();
}

//Funcion para estabilizar la lectura del potenciometro
uint16_t leer_pot_promediado(uint8_t muestras) {
    uint32_t suma = 0;
    for (uint8_t i = 0; i < muestras; i++) {
        suma += adc_read();  // Ya debe estar configurado el canal
        sleep_ms(2);         // Pequeña pausa entre lecturas
    }
    return suma / muestras;
}