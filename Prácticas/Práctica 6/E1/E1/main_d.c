/*
 * main_d.c
 *
 * Created: 22/04/2024 11:02:42
 *  Author: DCE
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TMR1.h"
#include "ADC.h"

volatile uint16_t pot_value = 0;

ISR(TIMER1_COMPA_vect)
{
	ADC_enableInt();
	ADC_START();
}

ISR(ADC_vect)
{
	pot_value = ADC;
	ADC_disableInt();
}

int main(void)
{
	DDRB |= (1<<DDB0) | (1<<DDB1);
	init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128);
	uint8_t channel = 0;
	ADC_select_channel(channel);
	TMR1_CTC_Init();
	TMR1_CTC_Set(7813); //~=500 ms
	TMR1_CTC_enaInterrupt();
	TMR1_HW_toggleOC1A();
	
	sei();
	
	TMR1_CTC_Start(DIV_CLK_1024);
	
	while (1)
	{
		if(pot_value > 512)
		PORTB |= (1<<PORTB0);
		else
		PORTB &= ~(1<<PORTB0);
	}
}