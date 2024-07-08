/*
 * E1.c
 *
 * Created: 11/03/2024 10:04:40
 * Author : DCE
 */ 


#include "USART.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "ADC.h"
#include "PORTS.h"
#include "LED_BUTTON.h"

int main(void)
{
	// Inicialización de GPIO y USART
	GPIO_init();
	USART0_init(UBRR_VALUE); // Asegúrate de que UBRR_VALUE esté definido correctamente en tu archivo USART.h
	
	// Inicialización del ADC
	init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128);
	uint8_t channel = 0;
	
	while (1)
	{
		// Leer valor del ADC
		uint16_t adc_value = ADC_Read_Single_Poll(channel);
		
		// Convertir el valor del ADC a una cadena de caracteres
		char adc_string[5]; // Suponiendo que el valor máximo del ADC es 1023
		utoa(adc_value, adc_string, 10); // Convierte el valor del ADC a una cadena decimal
		
		// Enviar la cadena a través de USART
		USART0_putString(adc_string);
		USART0_putchar('\n'); // Agrega un salto de línea para mejorar la legibilidad
		
		_delay_ms(100); // Espera un segundo antes de leer el ADC nuevamente (opcional)

		
		// Apagar todos los LEDs
		GPIO_1_OUT &= ~(0b11111111);
		
		// Lógica de encendido de LEDs (mantenida desde el código original)
		if (adc_value > 0 && adc_value <= 255)
		{
			LED_ON(GPIO_1_OUT, LED1_PIN);
		}
		else if (adc_value > 255 && adc_value <= 512)
		{
			LED_ON(GPIO_1_OUT, LED2_PIN);
		}
		else if (adc_value > 512 && adc_value <= 768)
		{
			LED_ON(GPIO_1_OUT, LED3_PIN);
		}
		else if (adc_value > 768 && adc_value <= 1023)
		{
			LED_ON(GPIO_1_OUT, LED4_PIN);
		}
		
	}
}

