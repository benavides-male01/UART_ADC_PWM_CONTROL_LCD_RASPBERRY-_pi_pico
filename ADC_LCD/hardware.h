#ifndef HARDWARE_H
#define HARDWARE_H

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"

#define UART_ID uart1
#define BAUD_RATE 115200
#define UART_TX_PIN 8
#define UART_RX_PIN 9

#define ADC_GPIO     27
#define ADC_CHN     1

#define LCD_ADDR 0x27
#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

#endif
