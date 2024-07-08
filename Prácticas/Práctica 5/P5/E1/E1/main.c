/*
 * E1.c
 *
 * Created: 11/03/2024 10:04:40
 * Author : DCE
 */ 

#include <avr/io.h>
#include "ADC.h"
#include "PORTS.h"
#include "LED_BUTTON.h"
#include "USART.h"


int main(void)
{
	GPIO_init();
	init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128);
	uint8_t channel = 0;
	while (1)
	{
		ADC = ADC_Read_Single_Poll(channel);
		
		if(ADC > 0 && ADC <= 255)
		{
			GPIO_1_OUT &= ~(0b11111111);
			LED_ON(GPIO_1_OUT, LED1_PIN);
		}
		
		if(ADC > 255 && ADC <= 512)
		{
			GPIO_1_OUT &= ~(0b11111111);
			LED_ON(GPIO_1_OUT, LED2_PIN);
		}
		
		if(ADC > 512 && ADC <= 768)
		{
			GPIO_1_OUT &= ~(0b11111111);
			LED_ON(GPIO_1_OUT, LED3_PIN);
		}
		
		if(ADC > 768 && ADC <= 1023)
		{
			GPIO_1_OUT &= ~(0b11111111);
			LED_ON(GPIO_1_OUT, LED4_PIN);
		}
	}
}

