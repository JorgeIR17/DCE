/// Define CPU frequency as 16 MHz
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PARAMETERS.h"

int main(void) {
	/** ------------ SETUP ------------------ */
	/// 1) Set pin 0-3 in PORTD as output pin
	DDRD |=(1<<DDD0) | (1<<DDD1) | (1<<DDD2) | (1<<DDD3);
	int cont = 0b00000000;
	
	/** ------------ LOOP ------------------- */
	while (1) {
		/// 1) LED OFF by clearing the pin PD3
		PORTD &= (~(1<<PORTD0)) & (~(1<<PORTD1)) & (~(1<<PORTD2)) & (~(1<<PORTD3));
		/// 2) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
		/// 3) LED ON by setting the pin PD3
		PORTD = PORTD | ~(cont);
		if(cont == 0b00001001)
			cont = 0b00000000;
		else
			cont++;
		/// 4) Delay of 500 milli-seconds
		_delay_ms(BLINK_TIME);
	}
}