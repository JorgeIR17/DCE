/*
 * BUZZER.c
 *
 * Created: 29/04/2024 10:54:08
 *  Author: DCE
 */ 

#include "BUZZER.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// ISR for Timer 0
ISR(TIMER0_COMPA_vect)
{
	TOGGLEBIT(PORTB, PORTB2);
}

// ISR for Timer 1
ISR(TIMER1_COMPA_vect)
{
	CLEARBIT(PORTB, PORTB2);
	TMR0_CTC_Stop();
	TMR1_CTC_Stop();
}