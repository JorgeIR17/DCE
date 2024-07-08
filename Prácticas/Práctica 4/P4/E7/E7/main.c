/*
 * E7.c
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

#define LED_COUNT_PORT PORTD // Define PORTD for LED count display
#define LED_COUNT_MASK 0xF0 // Define mask for LEDs PD4 to PD7

volatile char asciiChar = 'A'; // Initial ASCII character
volatile uint8_t buttonPressCount = 0; // Variable to count button presses

// External interrupt service routine for INT0
ISR(INT0_vect) {
	// Increment the ASCII character
	asciiChar++;
	// Reset to 'A' if ASCII character exceeds 'Z'
	if (asciiChar > 'Z') {
		asciiChar = 'A';
	}
	// Transmit the ASCII character via USART
	USART0_putchar(asciiChar);
	// Increment the button press count
	buttonPressCount++;
	// Display button press count using LEDs
	LED_COUNT_PORT = (LED_COUNT_PORT & ~LED_COUNT_MASK) | ((buttonPressCount << 4) & LED_COUNT_MASK);
}

// External interrupt service routine for INT1
ISR(INT1_vect) {
	// Decrement the ASCII character
	asciiChar--;
	// Reset to 'Z' if ASCII character goes below 'A'
	if (asciiChar < 'A') {
		asciiChar = 'Z';
	}
	// Transmit the ASCII character via USART
	USART0_putchar(asciiChar);
}

int main() {
	// Initialize GPIO ports
	GPIO_init();
	// Enable external interrupts for INT0 and INT1
	INT0_config(FALLING);
	INT1_config(FALLING);
	INT0_enable();
	INT1_enable();
	// Initialize USART
	USART0_init(UBRR_VALUE);
	// Enable USART RX interrupt
	USART0_enaInterrupt_RX();
	// Enable global interrupts
	sei();

	while (1) {
		// Main loop, interrupts handle the rest
	}

}

