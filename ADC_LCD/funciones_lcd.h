#ifndef _FUNCIONES_LCD_H_
#define _FUNCIONES_LCD_H_

#include <stdint.h>  // Muy importante para que reconozca uint8_t

void lcd_send(uint8_t data, uint8_t mode);
void lcd_init(void); 
void lcd_print(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear_line(uint8_t row);  // si la estás usando

#endif
