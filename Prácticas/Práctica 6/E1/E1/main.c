/*
 * E1.c
 *
 * Created: 22/04/2024 9:14:13
 * Author : DCE
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TMR1.h"

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1<<PORTB5);
}

int main(void)
{
    DDRB |= (1<<DDB5);
	TMR1_CTC_Init();
	TMR1_CTC_Set(7813); //~=500 ms
	TMR1_CTC_enaInterrupt();
	
	sei();
	
	TMR1_CTC_Start(DIV_CLK_1024);
	
    while (1) 
    {
    }
}

