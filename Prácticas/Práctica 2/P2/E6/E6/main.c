/*
 * E6.c
 *
 * Created: 19/02/2024 9:26:02
 * Author : DCE
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "PARAMETERS.h"
#include "PORTS.h"
#include "MACROS.h"

int main(void) {
	/** ------------ SETUP ------------------ */
	/// 1) Set pin 5 in PORTB as output pin
	GPI0_init();
	/** ------------ LOOP ------------------- */
	while (1) {
		/// 1) LED OFF by clearing the pin PB5
		CLEARBIT(GPI001, LED_MODE);
		/// 2) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
		/// 3) LED ON by setting the pin PB5
		SETBIT(GPI001_OUT, LED);
		/// 4) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
	}
}

