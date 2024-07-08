/*
 * E6.c
 *
 * Created: 04/03/2024 11:07:19
 * Author : DCE
 */ 

#define  F_CPU	16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PORTS.h"
#include "EXINT.h"
#include "USART.h"

ISR (USART_RX_vect) {
	char receivedData = USART0_getchar(); // Receive character from USART
	if (receivedData >= 'a' && receivedData <= 'z') {
		// Convert lowercase to uppercase
		receivedData -= ('a' - 'A');
	}
	USART0_putchar(receivedData); // Transmit the received or converted character
}

int main() {
	// Initialize USART
	USART0_init(UBRR_VALUE); // Pass UBRR_VALUE for baud rate

	// Enable USART RX interrupt
	USART0_enaInterrupt_RX();

	// Enable global interrupts
	sei();

	while (1) {
		// Main loop, interrupts handle the rest
	}

}

