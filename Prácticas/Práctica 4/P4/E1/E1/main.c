/*
 * E1.c
 *
 * Created: 04/03/2024 9:18:28
 * Author : DCE
 */ 

#include <avr/io.h>


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define BAUD 9600
#define	UBRR_VALUE ((F_CPU/(16UL*BAUD))-1)

void USART0_putchar (unsigned char data);
void USART0_putString (char *strPointer);


int main(void)
{
	//baud rate
	UBRR0H = (unsigned char)(UBRR_VALUE>>8);
	UBRR0L = (unsigned char)UBRR_VALUE;
	
	//Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	
	//Set speed: Normal Asynchronous (no change)
	//Set frame format: 8data, 1 stop bit, no parity
	
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	
	
    while (1) 
    {
		USART0_putString("Hello world \n\r");
    }
}

void USART0_putchar (unsigned char data)
{
	//polling (while UDRE0 is '0' keeps waiting)
	while(!(UCSR0A & (1<<UDRE0))){}
	
	//when UDRE0 = 1 -> available for transmittion
	
	UDR0 = data;
}

void USART0_putString (char *strPointer)
{
	//while *strPointer != NULL it sends a new character of the string
	while(*strPointer)
	{
		USART0_putchar(*strPointer);
		strPointer++;
	}
}