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
#include <stdbool.h>

#include "PARAMETERS.h"
#include "MACROS.h"
#include "PORTS.h"

bool GPIO_readButton()
{
	if((READ_PIN(PIND, PIND2)) == BUTTON_PRESSED)
	{
		///----------------------------------------------------------------
		/// 1.1. Wait for a time to avoid the pushbutton bounce
		_delay_ms(DEBOUNCE_TIME);
		///----------------------------------------------------------------
		/// 1.2. Check if the button is NOT already PRESSED
		if ((READ_PIN(PIND, PIND2)) != BUTTON_PRESSED)
		{
			/// 1.2.2 Wait for a time to avoid bouncing in pushbutton (release)
			return BUTTON_PRESSED;
		}
	}
	return !BUTTON_PRESSED;
}

int main(void)
{
	/** ------------ SETUP ------------------------*/
	///	1. Set pin as output for the LED
	GPI0_init();
	bool isButtonPressed = !BUTTON_PRESSED;
	///---------------------------------------------
	/// 2. Enable pull-up for the PUSHBUTTON
	/** ------------ LOOP ----------------------------------------*/
	while (1)
	{
		isButtonPressed = GPIO_readButton();
		_delay_ms(DEBOUNCE_TIME);
		if(isButtonPressed == BUTTON_PRESSED)
		{
			TOGGLEBIT(GPIO01_OUT, LED);
			isButtonPressed = !BUTTON_PRESSED;
		}
	}
}