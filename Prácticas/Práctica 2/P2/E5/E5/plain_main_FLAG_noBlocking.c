/**
	@file		main_noBlocking.c
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
#include <stdbool.h>

#include "PARAMETERS.h"

int main(void){
/**------------ Local variables ------------------------------*/	
	bool oldReadingPush	= true; // NOT_PRESSED
	bool newReadingPush	= true; // NOT_PRESSED
	bool statePush		= true; // NOT_PRESSED
/** ------------ SETUP ---------------------------------------*/
///	1. Set pin as output for the LED
DDRD	|= (1<<DDD3);
///---------------------------------------------
/// 2. Enable pull-up for the PUSHBUTTON
PORTD	|= (1<<PORTD2);
/** ------------ LOOP ----------------------------------------*/
    while (1)	
	 {
	 ///---------------------------------------------------------
	 /// 1. Read the pushbutton (First reading)
		oldReadingPush = (PIND & (1 << PIND2));
	 ///---------------------------------------------------------
	 /// 2. Wait for a time before to read the pushbutton again
		_delay_ms(TIME_BETWEEN_READINGS); // Wait for a second reading
	 ///---------------------------------------------------------
	 /// 3. Read again the pushbutton (Second reading)
		newReadingPush = (PIND & (1 << PIND2));
	 ///---------------------------------------------------------------------
	 /// 4. If the pushbutton state is NOT PRESSED (flag)	
	 if (statePush==true)
	 { // State NOT PRESSED	
		///---------------------------------------------------------------------
		/// 4.1. Check if the pushbutton is pressed (a falling-edge is detected)
		if ((oldReadingPush==true) && (newReadingPush==false))
		{		
			///--------------------------------------------------------------
			/// 4.1.1. Wait for avoiding the pushbutton bounce
			_delay_ms(DEBOUNCE_TIME); 
			///--------------------------------------------------------------
			/// 4.1.2. Change the flag to warn the pushbutton is pressed
			statePush=false; // PRESSED
		}
	 }
	 ///---------------------------------------------------------------------
	 /// 5. If the pushbutton state is PRESSED (flag)
	 else
	 { // State PRESSED   
	    ///--------------------------------------------------------------
	    /// 5.1. Check if the pushbutton is released (a rising-edge is detected)
			if ((oldReadingPush==false) && (newReadingPush==true))
			 {	
				///--------------------------------------------------------------
				/// 5.1.1. Change the flag to warn the pushbutton is released
					statePush=true;
				///--------------------------------------------------------------
				/// 5.1.2. If released, do the task: change the state of the LED
					PORTD ^= (1<< PORTD3);
				///--------------------------------------------------------------
				/// 5.3. Wait for a time to avoid bouncing in pushbutton (release)
					 _delay_ms(DEBOUNCE_TIME);
			 }
	 }		
	} // end while
} // end main
