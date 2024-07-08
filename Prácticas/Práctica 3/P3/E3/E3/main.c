/*
 * E3.c
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
///-------- Interrupt Service Routines --------------------------
/// If INT0 interrupt is enabled, each time the pushbutton is
/// pressed, the int interrupt is triggered. Then all the actions
/// written into the ISR are executed. When it finishes, the flag is
/// cleared and the main program continues.
	volatile uint8_t cont = 0;

volatile uint8_t counter = 0;
volatile uint8_t max_increment = 4;

ISR(INT0_vect) {
	_delay_ms(DEBOUNCE_TIME); // Espera para evitar rebotes en el botón
	if (!(READ_PIN(GPIO01_IN, BUTTON))) { // Si el botón está presionado
		if (counter < max_increment) {
			counter++; // Incrementa el contador solo si está por debajo del límite máximo
		}
		while (!(READ_PIN(GPIO01_IN, BUTTON))); // Espera hasta que se suelte el botón
	}
}

int main(void) {
	GPIO_init();

	SETBIT(EICRA, ISC01); // INT0 se activa por flanco descendente
	CLEARBIT(EICRA, ISC00);
	SETBIT(EIMSK, INT0); // Habilita la interrupción externa INT0

	sei(); // Habilita las interrupciones globales

	while (1) 
	{
		// Muestra el valor del contador en los LEDs (formato binario)
		GPIO_1_OUT = (GPIO_1_OUT & 0b00001111) | (counter << 4); // Actualiza solo los bits de los LEDs
	}
}


