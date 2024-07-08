/**
	@file		main.c
	@author		Mirian Cifredo
	@date		10/02/2022
    @brief		Toggle a LED by means a pushbutton
    @par		Description 
				Allow toggle a LED every time a pushbutton is pressed.
				In order to avoid a bouncing in the pushbutton, the system waits for a time
				until the state of the pushbutton is stable.
*/
/// Define CPU frequency as 16 MHz 
#define  F_CPU	16000000UL
#include <avr/io.h>	 			
#include <util/delay.h>

#include "PARAMETERS.h"


int main(void)
{
/** ------------ SETUP ------------------------*/
///	1. Set pin as output for the LED
	DDRD	|= (1<<DDD3);
///---------------------------------------------
/// 2. Enable pull-up for the PUSHBUTTON
	PORTD	|= (1<<PORTD2);
/** ------------ LOOP ----------------------------------------*/
	 while (1)
	 {	 
	 ///---------------------------------------------
	 /// 1. If the pushbutton is pressed
		 if (!(PIND & (1 << PIND2)))
		 {
			 ///----------------------------------------------------------------
			 /// 1.1. Wait for a time to avoid the pushbutton bounce
			 _delay_ms(DEBOUNCE_TIME);
			 ///----------------------------------------------------------------
			 /// 1.2. Wait while the button keeps pressed
			 while(!(PIND & (1 << PIND2)));
			 ///----------------------------------------------------------------
			 /// 1.3.When the pushbutton is released, do the task: change the state of the LED
			 PORTD ^= (1<< PORTD3);
			 ///----------------------------------------------------------------
			 /// 1.4. Wait for a time to avoid bouncing in pushbutton (release)
			 _delay_ms(DEBOUNCE_TIME);
		 }
	 }	 
 }

