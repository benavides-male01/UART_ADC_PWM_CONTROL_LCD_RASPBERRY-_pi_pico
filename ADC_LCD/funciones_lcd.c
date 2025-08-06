#include <stdio.h>
#include "systick.h"
#include "hardware.h"
#include "funciones_lcd.h"

// Envía un byte al LCD usando interfaz I2C en modo 4 bits
void lcd_send(uint8_t data, uint8_t mode) {
    uint8_t high = (data & 0xF0) | mode | 0x08;         // Parte alta + modo + retroiluminación
    uint8_t low  = ((data << 4) & 0xF0) | mode | 0x08;  // Parte baja + modo + retroiluminación
    uint8_t cmds[] = {high | 0x04, high, low | 0x04, low}; // Pulsos de Enable

    // Enviar los 4 bytes al LCD por I2C
    i2c_write_blocking(I2C_PORT, LCD_ADDR, cmds, 4, false);
}

// Inicializa el LCD en modo 4 bits, 2 líneas, sin cursor
void lcd_init() {
    sleep_ms(50);  // Espera inicial (LCD se estabiliza)

    // Secuencia de inicialización para modo 4 bits
    lcd_send(0x03, 0); sleep_ms(5);
    lcd_send(0x03, 0); sleep_us(100);
    lcd_send(0x03, 0); sleep_us(100);
    lcd_send(0x02, 0);  // Cambia a modo 4 bits

    lcd_send(0x28, 0);  // 2 líneas, matriz 5x8
    lcd_send(0x0C, 0);  // Display encendido, sin cursor
    lcd_send(0x01, 0); sleep_ms(2);  // Limpia pantalla
    lcd_send(0x06, 0);  // Cursor se mueve a la derecha
}

// Imprime una cadena en la posición actual del cursor
void lcd_print(const char *str) {
    while (*str) {
        lcd_send(*str++, 1);  // Enviar cada carácter en modo "datos"
    }
}

// Coloca el cursor en una posición (fila 0 o 1, columna 0 a 15)
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send(addr, 0);  // Enviar dirección al LCD
}

// (OPCIONAL) Limpia una línea específica sin usar lcd_clear total
void lcd_clear_line(uint8_t row) {
    lcd_set_cursor(row, 0);
    lcd_print("                ");  // 16 espacios para limpiar
    lcd_set_cursor(row, 0);
}
