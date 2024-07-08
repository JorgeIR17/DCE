/*
 * E3.c
 *
 * Created: 15/02/2024 10:38:56
 * Author : DCE
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	/* ------------ SETUP ----------------------------------------*/
	// 1. Set LED pin as output. All the I/O pins are inputs by default.
	DDRD |= (1<<DDD3);
	//---------------------------------------------------------------
	// 2. Enable the Pull-up resistor for the input PUSHBUTTON
	PORTD |= (1<<PORTD2); // Explained in datasheet or page 5

    /* ------------ LOOP ----------------------------------------
    Read the state of the pushbutton to show it onto a LED.
    Keep in mind that the read value when the PUSHBUTTON
    is released is '1' due to the pull-up resistor.
    ----------------------------------------------------------*/
    while (1) {
	    //----------------------------------------------------------
	    // 1. Read the pushbutton (read the whole PIND register)
	    // 2. If PUSHBUTTON is pressed, then PIND2=’0’
	    if (! (PIND & (1 << PIND2))) { // (1<<PIND2) <-> “0000 0100”
		    // ------------------------------------------------------------------
		    // PIND | MASK |
		    //-------------------------------------------------------------------
		    // If (XXXX X1XX & 0000 0100 = 0000 0100) ? Result is not Zero because
		    // PIND2=’1’ (Pushbutton is released, not pressed)
		    //
		    // If (XXXX X0XX & 0000 0100 = 0000 0000) ? Result is Zero because
		    // PIND2=’0’ (Pushbutton pressed)
		    //--------------------------------------------------------------------
		    // Not Zero is TRUE and Zero is false for the If structure
		    //--------------------------------------------------------------------
		    // 3. Switch ON the LED
		    PORTD |= (1<<PORTD3);
		    //-------------------------------------------------------------------
	    }
	    else {
		    //-------------------------------------------------------------------
		    // 4. else switch OFF the LED
		    PORTD &= (~(1<<PORTD3));
		    //-------------------------------------------------------------------
	    }
    }
}

