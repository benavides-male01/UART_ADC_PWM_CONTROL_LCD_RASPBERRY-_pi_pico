# ⚙️🦾 Proyecto ADC_LCD – Placa 1

Este programa corre en una Raspberry Pi Pico y es responsable de:

- Leer un valor analógico desde un potenciómetro (ADC)
- Enviar ese valor por UART a otra placa (UART_LED)
- Regular la intensidad del LED con PWM
- Recibir un porcentaje de brillo desde la placa UART_LED
- Mostrar el porcentaje en un LCD 16x2 (comunicado por I2C)
- Señalizar si el brillo está aumentando o disminuyendo

## 🔌 Periféricos utilizados

- ADC
- PWM
- UART (115200, 8N1)
- LCD 16x2 con interfaz I2C
- LED indicador (para subir/bajar)

## 📁 Archivos importantes

- `main.c` – Lógica principal del programa
- `funciones_lcd.c/.h` – Control del LCD
- `hardware.h` – Definiciones de pines y periféricos
- `systick.c/.h` – Temporización

## 📦 Dependencias

Este proyecto utiliza el **SDK oficial de Raspberry Pi Pico** y se construye con **CMake**.

![Montaje del circuito en protoboard](img/montaje.jpg)
