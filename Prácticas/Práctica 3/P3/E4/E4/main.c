/*
 * E4.c
 *
 * Created: 26/02/2024 9:45:20
 * Author : DCE
 */ 


#include <avr/io.h>


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "PORTS.h"
#include "MACROS.h"
#include "PARAMETERS.h"
#include "EX_INT.h"


#define ALL_ON 0
#define ODD_ON 1
#define EVEN_ON 2
#define ODD_OFF 3

volatile uint8_t state = ALL_ON;


ISR(INT0_vect) {
	_delay_ms(DEBOUNCE_TIME); // Debounce delay
	if (!(READ_PIN(GPIO01_IN, BUTTON))) { // If the button is pressed
		state++; // Move to the next state
		if (state > ODD_OFF) state = ALL_ON; // Reset if it exceeds the maximum state
		while (!(READ_PIN(GPIO01_IN, BUTTON))); // Wait until the button is released
	}
}

int main(void) {
	GPIO_init();

	INT0_config(FALLING); // Configure external interrupt INT0 for falling edge detection
	INT0_enable(); // Enable external interrupt INT0

	sei(); // Enable global interrupts

	while (1) {
		switch (state) {
			case ALL_ON:
			GPIO_1_OUT = 0b11110100; // Turn on all LEDs (pins 7, 6, 5, 4)
			break;
			case ODD_ON:
			GPIO_1_OUT = 0b10100100; // Turn on odd LEDs (pins 7, 5)
			break;
			case EVEN_ON:
			GPIO_1_OUT = 0b01010100; // Turn on even LEDs (pins 6, 4)
			break;
			case ODD_OFF:
			GPIO_1_OUT = 0b00000100; // Turn off all LEDs
			break;
			default:
			break;
		}
	}
}



