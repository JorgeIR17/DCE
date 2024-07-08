//#define  F_CPU 16000000UL
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
	uint16_t res = 0;
	for(uint8_t i = 0; i < times; i++)
    {
		res += ADC_Read_Single_Poll(channel);
	}

	switch(times)
    {
		case 1: break;
		case 2: res = res >> 1; break;
		case 4: res = res >> 2; break;
		case 8: res = res >> 3; break;
		case 16: res = res >> 4; break;
		case 32: res = res >> 5; break;
		default: res/= times; break;
	}
	return res;
}
