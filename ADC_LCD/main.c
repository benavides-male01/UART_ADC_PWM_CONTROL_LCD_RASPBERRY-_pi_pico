
#include <stdio.h>
#include "systick.h"
#include "hardware.h"
#include "funciones.h"
#include "funciones_lcd.h"
uint16_t resu_adc;
uint8_t valor_adc_resumido, porcentaje;
uint8_t simbolo;

int main() {
    // Inicializa UART, ADC, GPIO
    init();  

    // Inicializa I2C para el LCD
    i2c_init(I2C_PORT, 100 * 1000);  // 100kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    lcd_init();  // Inicializa el LCD

    uint8_t brillo_anterior = 255;

    while (1) {
        //Leer ADC localmente
        resu_adc= leer_pot_promediado(16);

        //Enviar ADC
        valor_adc_resumido = resu_adc/16;  // 4095 / 16 ≈ 255 
        uart_putc(UART_ID, valor_adc_resumido);

        //Esperar una respuesta con el porcentaje
        if (uart_is_readable(UART_ID)) {
            porcentaje = uart_getc(UART_ID);

            // Solo actualizar si cambió el valor
            if (porcentaje != brillo_anterior) {
            
                if (porcentaje > brillo_anterior)
                    simbolo = '+';
                else if (porcentaje < brillo_anterior)
                    simbolo = '-';
                else
                    simbolo = '=';
            
                brillo_anterior = porcentaje;
            
                char buffer[17];  // 16 caracteres + nulo
                sprintf(buffer, "Brillo:%3d%% %c", porcentaje, simbolo);
                lcd_set_cursor(0, 0);
                lcd_print(buffer);
            }
            
        }
        sleep_ms(100);  // Pausa para evitar saturar la UART
    }
}
