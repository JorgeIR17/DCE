/// Define CPU frequency as 16 MHz
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PARAMETERS.h"

int main(void) {
	/** ------------ SETUP ------------------ */
	/// 1) Set pin 5 in PORTB as output pin
	DDRB |=(1<<DDB5);
	/** ------------ LOOP ------------------- */
	while (1) {
		/// 1) LED OFF by clearing the pin PB5
		PORTB &=~(1<<PORTB5);
		/// 2) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
		/// 3) LED ON by setting the pin PB5
		PORTB |=(1<<PORTB5);
		/// 4) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
	}
}
