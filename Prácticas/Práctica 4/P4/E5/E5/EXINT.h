#ifndef EXINTH_
#define EXINTH_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LOW_LEVEL 0 // Decimal value equivalent to ICS01=0 and ICS00=0
#define CHANGE 1 // Decimal value equivalent to ICS01=0 and ICS00=1
#define FALLING 2 // Decimal value equivalent to ICS01=1 and ICS00=0
#define RISING 3 // Decimal value equivalent to ICS01=1 and ICS00=1

static inline void INT0_config (uint8_t typeTrigger)    {EICRA |= typeTrigger;}

static inline void INT1_config (uint8_t typeTrigger)    {EICRA |= (typeTrigger<<ISC10);}

static inline void INT0_enable()                        {EIMSK |= (1<<INT0);}

static inline void INT0_disable()                       {EIMSK &= ~(1<<INT0);}

static inline void INT1_enable()                        {EIMSK |= (1<<INT1);}

static inline void INT1_disable()                       {EIMSK &= ~(1<<INT1);}

static inline void PCINT_enable(uint8_t PCINT_EN)       {PCICR |= (1<<PCINT_EN);}

static inline void PCINT0_pinSelect(uint8_t pin)        {PCMSK2 |= (1<<pin);}

static inline void PCINT1_pinSelect(uint8_t pin)        {PCMSK2 |= (1<<pin);}

static inline void PCINT2_pinSelect(uint8_t pin)        {PCMSK2 |= (1<<pin);}

#endif /* EX_INT_H_*/