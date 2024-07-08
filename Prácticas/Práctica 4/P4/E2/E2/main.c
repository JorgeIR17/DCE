/*
 * E2.c
 *
 * Created: 04/03/2024 9:18:28
 * Author : DCE
 */ 

#include <avr/io.h>

#include "USART.h"

#include <avr/interrupt.h>
#include <util/delay.h>




int main(void)
{
	char charReceived;
	
	USART0_init(UBRR_VALUE);
	USART0_putString("USART inicializada\n\r");
	
    while (1) 
    {
		charReceived = USART0_getchar();
		USART0_putchar(charReceived);
    }
}

