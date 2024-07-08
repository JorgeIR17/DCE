/*
 * E5.c
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

ISR (INT0_vect){
	/// 1.- When the pushbutton triggers the INT0 the TX interrupt
	/// is enabled. When UDRE0 signals the USART is available,
	/// the UDRE interrupts is triggered. Then, it sends the message once.
	USART0_enaInterrupt_TX();
}
//-------------------------------------------------------------------
ISR (USART_UDRE_vect){
	/// Once the TX interrupt is enabled, every time the buffer is empty,
	/// a new character is sent.
	/// Once the whole message has been sent, the TX interrupt is disabled to
	/// avoid send the message again.
	//-----------------------------------------------------
	// SOL_1 - (BLOCKING!!!)
	// USART0_putString("Hello world \n\r");
	// USART0_disableInterrupt_TX();
	//------------------------------------------------------
	
	//--------------------------------------------------------
	// SOL_2 - (NON-BLOCKING!!!)
	// "Static", in other case the pointer is reset and "H" is
	// sent continuously.
	static char *strPointer="Hello World\n\r";
	if(*strPointer!= 0)
	{
		UDR0 = *strPointer;
		strPointer++;
		// As the interrupt is enabled, every time the UDR0 is empty
		// the ISR triggers again.
	}
	else
	{
		// Disable the TX IRQ when the message has been transmitted
		USART0_disableInterrupt_TX();
		// Reset the pointer
		strPointer="Hello World\n\r";
	}
	//-------------------------------------------------------------
}


//-------------------------------------------------------------------

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
	//----------------------------------------------------------
	/// 4. Enable global interrupts
	sei();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1){
		
	}
}

