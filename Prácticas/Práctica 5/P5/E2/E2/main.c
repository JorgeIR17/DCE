/*
 * E2.c
 *
 * Created: 11/03/2024 10:04:40
 * Author : DCE
 */ 


#include "USART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h" // Assuming you have ADC functions in ADC.h
#include "PORTS.h" // Assuming you have GPIO initialization in PORTS.h
#include "EX_INT.h"
#include "LED_BUTTON.h"
#include "PARAMETERS.h"

#define LED_PIN PORTB0 // Assuming LED is connected to PB0

volatile uint16_t ldrvalue = 0;


// ADC interrupt service routine
ISR(ADC_vect) {
	ldrvalue = ADC; // Read ADC value
	if (ldrvalue < SETPOINT) {
		// If ambient light is below threshold, switch on LED
		LED_ON(PORTB, LED_PIN);
		} else {
		// Otherwise, switch off LED
		LED_OFF(PORTB, LED_PIN);
	}
	
	ADC_START();
}

int main() {
	DDRB |= (1 << LED_PIN);
	init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128);
	ADC_enableInt(); // Enable ADC interrupt
	ADC_select_channel(0); // Set ADC input channel to PC0
	sei(); // Enable global interrupts

	while (1) {
		_delay_ms(SAMPLE_TIME);
	}

}


