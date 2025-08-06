#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "hardware.h"
#include "funciones.h"

uint16_t slice;
uint16_t chan;

void init() {
    stdio_init_all();

    // Inicialización del LED
    
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);

    // Configuración del PWM
    slice = pwm_gpio_to_slice_num(LED_PIN);
    chan = pwm_gpio_to_channel(LED_PIN);
    pwm_set_clkdiv_int_frac(slice, 15, 4);     // fPWM base ≈ 8.2 MHz
    pwm_set_wrap(slice, 4095);                 // Resolución de 12 bits
    pwm_set_enabled(slice, true);             // Habilita el PWM

    // Inicialización de la UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_pull_up(UART_RX_PIN);

 }
