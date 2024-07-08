/*
 * E1.c
 *
 * Created: 26/02/2024 9:23:51
 * Author : DCE
 */ 

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
ISR(INT0_vect) {
	///--------------------------------------------------------
	/// 1.- Toggle the red LED
	///--------------------------------------------------------
	TOGGLEBIT (GPIO_1_OUT, RED_LED_PIN); // Toggle the RED_LED
	//--------------------------------------------------------------------
	// 2. To avoid a new interrupt due to a falling edge caused by bouncing
	//--------------------------------------------------------------------
	_delay_ms (100); // Although is not recommended
}

int main(void) {
	/// ------------ SETUP ----------------------------------------
	/// -----------------------------------------------------------
	/// 1.- Configure ports
	/// -----------------------------------------------------------
	GPIO_init();
	/// -----------------------------------------------------------
	/// 2.- Configure external interrupt
	/// -----------------------------------------------------------
	EICRA = (1<<ISC01) |(0<<ISC00) | // INT0 is triggered by a falling edge
	(0<<ISC11) |(0<<ISC10); // INT1 is set as default value (0)
	EIMSK |= (1<<INT0); // Enable the ISR of INT0;
	/// -----------------------------------------------------------
	/// 3.- Enable global interrupts
	/// -----------------------------------------------------------
	sei(); // Equivalent to SREG |=(1<<I);
	///------------ LOOP ----------------------------------------
	while (1) {
		/// -----------------------------------------------------------
		/// 1.- Toggle the green LD
		/// -----------------------------------------------------------
		TOGGLEBIT (GPIO_1_OUT, GREEN_LED_PIN);
		_delay_ms(BLINK_TIME);
	}
}


