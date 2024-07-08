#define  F_CPU 16000000UL
#include <avr/io.h>
#include "ADC.h"

//----------------------------------------------------------------------
uint16_t ADC_Read_Single_Poll(uint8_t channel)
{
	ADCSRA |= (1<<ADIF);
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
	ADMUX |= (channel << MUX0);
	ADCSRA |= (1<<ADSC);

	while((ADCSRA && (1<<ADIF))==0){}

	return ADC;
}

uint16_t ADC_Read_Multiple_Poll(uint8_t channel, uint8_t times)
{
	ADC_Read_Single_Poll(channel);
	uint16_t aux = 0;
	for(uint8_t i = 0; i < times; i++)
    {
		aux += ADC_Read_Single_Poll(channel);
	}

	switch(times)
    {
		case 1: break;
		case 2: aux = aux >> 1; break;
		case 4: aux = aux >> 2; break;
		case 8: aux = aux >> 3; break;
		case 16: aux = aux >> 4; break;
		case 32: aux = aux >> 5; break;
		default: aux/= times; break;
	}
	return aux;
}
