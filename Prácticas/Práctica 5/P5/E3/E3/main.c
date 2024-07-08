/*
 * E3.c
 *
 * Created: 11/03/2024 10:04:40
 * Author : DCE
 */ 


#include "USART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "PORTS.h" 
#include "EX_INT.h"
#include "LED_BUTTON.h"
#include "PARAMETERS.h"
#include <stdlib.h>

#define LED_PIN PORTB0

volatile uint16_t ldr_value = 0;

volatile uint16_t pot_value = 0;



int main() {
	DDRB |= (1<<LED_PIN);
	// Initialize ADC
	init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128);
	// Initialize USART
	USART0_init(UBRR_VALUE);
	
	while (1) {
		char adc_string[5];
		// Show menu via serial communication
		USART0_putString("Menu:\r\n");
		USART0_putString("1. Measurement of the LDR\r\n");
		USART0_putString("2. Measurement of the potentiometer\r\n");
		USART0_putString("Enter your choice: ");

		// Wait for user input
		unsigned char choice = USART0_Getchar();
		USART0_putchar(choice);
		USART0_putString("\r\n");

		// Perform measurement based on user choice
		switch (choice) {
			case '1':
			{
			// Read LDR value
			ldr_value = ADC_Read_Multiple_Poll(0, 16);
			if(ldr_value < SETPOINT)
				LED_ON(PORTB, LED_PIN);
			else
				LED_OFF(PORTB, LED_PIN);
			utoa(ldr_value, adc_string, 10); // Convierte el valor del ADC a una cadena decimal
			// Send LDR value via serial communication
			USART0_putString("LDR value: ");
			USART0_putString(adc_string);
			USART0_putString("\r\n");
			}
			break;
			case '2':
			{
			// Read potentiometer value
			pot_value = ADC_Read_Multiple_Poll(1, 16);
			utoa(pot_value, adc_string, 10); // Convierte el valor del ADC a una cadena decimal
			// Send potentiometer value via serial communication
			USART0_putString("Potentiometer value: ");
			USART0_putString(adc_string);
			USART0_putString("\r\n");
			}
			break;
			default:
			// Invalid choice
			USART0_putString("Invalid choice\r\n");
			break;
		}

		_delay_ms(1000); // Delay to prevent flickering in the serial monitor
	}

}

