#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/systick.h"

volatile uint32_t u32_tick_count;

void init_systick(void){ 
    systick_hw->csr = 0; 	    //Disable 
    systick_hw->rvr = 124999UL; //Standard System clock (125Mhz)/ (rvr value + 1) = 1ms 
    systick_hw->csr = 0x7;      //Enable Systic, Enable Exceptions	
}

extern void isr_systick(void){ //Rewrite of weak systick IRQ in crt0.s file
    u32_tick_count++;     
}

uint32_t get_systick(void){
	return u32_tick_count;
}