/*
 * main_d.c
 *
 * Created: 26/03/2024 11:40:12
 *  Author: Jorge
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PORTS.h"
#include "MACROS.h"
#include "PARAMETERS.h"
#include "EX_INT.h"

volatile uint8_t counter = 0;
volatile uint8_t max_increment = 4;

ISR(INT0_vect) {
	_delay_ms(DEBOUNCE_TIME); // Espera para evitar rebotes en el bot�n
	if (!(READ_PIN(GPIO01_IN, BUTTON))) { // Si el bot�n est� presionado
		if (counter < max_increment) {
			counter++; // Incrementa el contador solo si est� por debajo del l�mite m�ximo
		}
		while (!(READ_PIN(GPIO01_IN, BUTTON))); // Espera hasta que se suelte el bot�n
	}
}

int main(void) {
	GPIO_init();

	INT0_config(FALLING); // Configura la interrupci�n externa INT0 para que se active en flanco descendente

	INT0_enable(); // Habilita la interrupci�n externa INT0

	sei(); // Habilita las interrupciones globales

	while (1) {
		// Muestra el valor del contador en los LEDs (formato binario)
		GPIO_1_OUT = (GPIO_1_OUT & 0b00001111) | (counter << 4); // Actualiza solo los bits de los LEDs
	}
}
