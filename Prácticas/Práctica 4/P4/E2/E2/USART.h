/*
 * USART.h
 *
 * Created: 04/03/2024 9:53:29
 *  Author: DCE
 */ 


#ifndef USART_H_
#define USART_H_

//#ifdef F_CPU
//#undef F_CPU
#define F_CPU 16000000UL
//#endif


#define BAUD 9600
#define UBRR_VALUE ((F_CPU/(16UL*BAUD))-1)

void USART0_putchar(unsigned char data)
{
	while(!(UCSR0A & (1 << UDRE0))){}
	UDR0 = data;
}

void USART0_putString(char *strPointer)
{
	while(*strPointer){
		USART0_putchar(*strPointer);
		strPointer++;
	}
}

char USART0_getchar(void)
{
	while(!(UCSR0A & (1 << RXC0))){}
	return UDR0;
}

static inline void USART0_init(uint16_t valueUBBR)
{
	UBRR0H = (unsigned char) (UBRR_VALUE>>8);
	UBRR0L = (unsigned char) UBRR_VALUE;
	///--------------------------------------------------------
	/// 2.- enable receiver and transmitter
	///--------------------------------------------------------
	UCSR0B |= (1 << RXEN0) | (1<<TXEN0);
	///--------------------------------------------------------
	/// 3.- set the speed: normal Asynchronous
	/// 4.- set frame format:
	UCSR0C |= (1<<UCSZ01) | (1<< UCSZ00);
}

static inline void USART0_enaInterrupt_RX()
{
	UCSR0B |= (1<<RXCIE0);
}

static inline void USART0_disableInterrupt_RX()
{
	UCSR0B &= ~(1<<RXCIE0);
}

static inline void USART0_enaInterrupt_TX()
{
	UCSR0B |= (1<<UDRIE0);
}

static inline void USART0_disableInterrupt_TX()
{
	UCSR0B &= ~(1<<UDRIE0);
}

#endif /* USART_H_ */