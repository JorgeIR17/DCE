/*
 * E4.c
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

/// -------------  ISR functions -----------------------------------
ISR (INT0_vect)
///-------------------------------------------------------
{
	static char datum = 0x21;
	//-------------------------------------------------------------
	// 1.- Check if the USART is available for sending
	//-------------------------------------------------------------
	USART0_putchar(datum);			// BLOCKING!!! due to the "while" in the function.
	//------------------------------------------------------------------
	// 2.- If the char has been sent, increment the ASCII while is in the range.
	//-----------------------------------------------------------------
	if( datum >= 0x7F )
	///-------------------------------------------------------
	{// 2.1.- If the last ASCII character has been reached, restart.
		datum = 0x21;
	}							// Re-start "datum"
	else
	///-------------------------------------------------------
	{// 2.2.- Send the next ASCII char
		datum++;
	}
	///-------------------------------------------------------
}

//-------------------------------------------------------------------
ISR (USART_RX_vect) {
	// Clear the 4 MSB in PORTD (mask 0x0F). Keep the value (Rpull-up)
	// OR with the 4 LSB of the ASCII char and shift left 4 bits
	GPIO_1_OUT = (GPIO_1_OUT & 0b00001111) | ((UDR0 & 0x0F) << LED0_PIN);
}


//----------------------------------------------------------------------------------

int main(){
	/// -------------  SETUP -----------------------------------
	/// 1. Config ports (4 LED and pushbutton - "PORTS.h")
	GPIO_init();
	//---------------------------------------------------------
	/// 2. External interrupt setup (INT0 - Pushbutton)
	INT0_config(FALLING);
	INT0_enable();
	//----------------------------------------------------------
	/// 3. USART setup (9600 8N1 - Keyboard)
	USART0_init(UBRR_VALUE);
	USART0_enaInterrupt_RX();
	//----------------------------------------------------------
	/// 4. Enable global interrupts
	sei();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1){
	}
}

