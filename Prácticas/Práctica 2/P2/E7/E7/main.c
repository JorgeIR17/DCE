/*
 * E7.c
 *
 * Created: 19/02/2024 9:58:33
 * Author : DCE
 */ 

/// Define CPU frequency as 16 MHz 
#define  F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "PARAMETERS.h"
#include "MACROS.h"
#include "PORTS.h"


int main(void)
{
	/** ------------ SETUP ------------------------*/
	///	1. Set pin as output for the LED
	GPI0_init();
	///---------------------------------------------
	/// 2. Enable pull-up for the PUSHBUTTON
	/** ------------ LOOP ----------------------------------------*/
	while (1)
	{
		if(!(READ_PIN(PIND, PIND2)))
		{
			///----------------------------------------------------------------
			/// 1.1. Wait for a time to avoid the pushbutton bounce
			_delay_ms(DEBOUNCE_TIME);
			///----------------------------------------------------------------
			/// 1.2. Check if the button is NOT already PRESSED
			if (READ_PIN(PIND, PIND2))
			{
				///----------------------------------------------------------------
				/// 1.2.1. If released, do the task: change the state of the LED
				TOGGLEBIT(GPIO01_OUT, LED);
				///----------------------------------------------------------------
				/// 1.2.2 Wait for a time to avoid bouncing in pushbutton (release)
				_delay_ms(DEBOUNCE_TIME);
			}
		}
	}
}