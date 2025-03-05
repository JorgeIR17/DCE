#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MACROS.h"
#include "TMR0.h"
#include "TMR1.h"

#define STARTING_SOUND 62
#define STARTING_SOUND_DURATION 1562 // 100 ms

#define MATCH_SOUND 39
#define MATCH_SOUND_DURATION 7812 // 500 ms

#define FAIL_SOUND 125
#define FAIL_SOUND_DURATION 15625 // 1000 ms


#define TICKS_1_sec		15625
#define TICKS_500_msec	7812
#define TICKS_100_msec  1562

// Function to set buzzer pin as output
static inline void buzzerInit()
{
	DDRB |= (1 << DDB2); // Pin MOSI (PB2) as output
	
	TMR0_CTC_Init();
	TMR0_CTC_enaInterrupt();
	TMR1_CTC_Init();
	TMR1_CTC_enaInterrupt();
	
	sei();
}

static inline void playSound_TMR(uint8_t nTicks_beepFreq, uint16_t nTicks_beepDuration)
{
    TMR0_CTC_Set(nTicks_beepFreq);
	TMR1_CTC_Set(nTicks_beepDuration);
	
	TMR0_CTC_Start(DIV_CLK_256);
	TMR1_CTC_Start(DIV_CLK_1024);
}

#endif