/*
 * E3.c
 *
 * Created: 04/03/2024 10:37:17
 * Author : DCE
 */ 

#include <avr/io.h>
#include "USART.h"
#include <avr/interrupt.h>
#include <util/delay.h>

static inline void mainMenu(void)
{
	USART0_putString("---------------------------\n\r"
	"This is the main menu. Select one choice:\n\r"
	"---------------------------\n\r"
	"a: choice 'a'\n\r"
	"b: choice 'b'\n\r"
	"\n\r"
	"h: Show the menu again\n\r"
	"---------------------------\n\r");
}

int main(void)
{
	char key;
	USART0_init(UBRR_VALUE);
	mainMenu();
	
	while(1)
	{
		key = USART0_getchar();
		
		switch(key)
		{
			case 'a':
			USART0_putString("You pressed an 'a'.\n\r");
			break;
			case 'b':
			USART0_putString("You pressed an 'b'.\n\r");
			break;
			case 'h':
			USART0_putString("\f");
			mainMenu();
			break;
			default:
			USART0_putString("I don't know what to do with that key.\n\r");
			break;
		}
	}
}

