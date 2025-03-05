#ifndef TMR4_H_
#define TMR4_H_

#include <avr/io.h>

#define TMR4_DIV_CLK_1	   1
#define TMR4_DIV_CLK_2	   2
#define TMR4_DIV_CLK_4	   3
#define TMR4_DIV_CLK_8	   4
#define TMR4_DIV_CLK_16    5
#define TMR4_DIV_CLK_32	   6
#define TMR4_DIV_CLK_64	   7
#define TMR4_DIV_CLK_128   8
#define TMR4_DIV_CLK_256   9
#define TMR4_DIV_CLK_512   10
#define TMR4_DIV_CLK_1024  11
#define TMR4_DIV_CLK_2048  12
#define TMR4_DIV_CLK_4096  13
#define TMR4_DIV_CLK_8192  14
#define TMR4_DIV_CLK_16384 15


static inline void TMR4_PWM_Phase_Init()
{
	DDRC |= (1<<DDC6); // Set OC4A (PC6) as output
	DDRD |= (1<<DDD7); // Set OC4D (PD7) as output

	TCCR4A |= (1<<COM4A0) | (1<<PWM4A);
	TCCR4A &= ~(1<<COM4A1);

	TCCR4C |= (1<<COM4D1) | (1<<PWM4D);
	TCCR4C &= ~(1<<COM4D0);

	TCCR4D &= ~(1<<WGM41);
	TCCR4D |= (1<<WGM40);
}

inline void TMR4_PWM_Phase_Start(uint8_t divClock)
{
    TCNT4 = 0; // Reset counter

    TCCR4B &= 0b11110000; // Clear CS40, CS41, CS42
    TCCR4B |= (divClock<<CS40); 
}

inline void TMR4_PWM_Phase_Duty(uint8_t valueOCR4A, uint8_t valueOCR4D)
{
    OCR4A = ~(valueOCR4A); 
    OCR4D = valueOCR4D; 
}

inline void TMR4_PWM_Phase_Stop()
{
	TCCR4B &= 0b11110000;

	TMR4_PWM_Phase_Duty(0, 0);
}

#endif /* TMR4_H_ */
