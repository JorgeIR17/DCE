/*
 * examen.c
 *
 * Created: 15/04/2024 8:30:51
 * Author : Jorge
 */ 

#include "USART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "PORTS.h"
#include "EX_INT.h"
#include "PARAMETERS.h"
#include <stdlib.h>
#include <avr/eeprom.h>

/*Variables*/

typedef enum
{
	STATE_MODE,	
	STATE_LDR,
	STATE_POT
}States;

static volatile uint8_t mode = PRODUCTION; //default mode
uint16_t SET_POINT; //set_point value
uint16_t SET_POINT_COPY;

/*Functions*/

static void init_LED_MODE()
{
	for(uint8_t i = 0; i < 3; i++)
	{
		GPIO_1_OUT |= (1<<LED_MODE); //LED ON
		_delay_ms(BLINK_TIME);
		GPIO_1_OUT &= ~(1<<LED_MODE); //LED OFF
		_delay_ms(BLINK_TIME);
	}
}

/*BUTTON_MODE*/
ISR(INT0_vect)
{
	mode = CONFIGURATION;
}

/*BUTTON_INTRO*/
ISR(INT1_vect)
{
	mode = PRODUCTION;
	SET_POINT = SET_POINT_COPY; //we assign the copied value on the main function to save it
	
	eeprom_write_byte(EEPROM_ADDRESS, SET_POINT); //8 lsb
	eeprom_write_byte(EEPROM_ADDRESS+1, SET_POINT>>8); //8 msb
}

int main(void)
{
    GPIO_init(); // I/O ports
	init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128); //ADC
	USART0_init(UBRR_VALUE); //USART
	sei(); //enable interrupts
	
	
	INT0_config(FALLING);
	INT1_config(FALLING);
	INT0_enable(); //BUTTON_MODE
	INT1_enable(); //BUTTON_INTRO
	
	uint16_t ldr_value;
	char output[5]; //used to show the value
	
	/*We load the value from eeprom (EEPROM_ADDRESS+1)<<8: 8 msb*/
	SET_POINT = (eeprom_read_byte(EEPROM_ADDRESS + 1)<<8 | eeprom_read_byte(EEPROM_ADDRESS));
	
	SET_POINT_COPY = SET_POINT; //we copy the stored value
	
	/*FSM Variables*/
	
	States CurrentState = STATE_MODE;
	States NextState = STATE_MODE;
	
	init_LED_MODE();
	
    while(1) 
    {
		switch(CurrentState)
		{
			case STATE_MODE:
			{
				if(mode == PRODUCTION) // production mode
				{
					NextState = STATE_LDR;
					GPIO_1_OUT |= (1<<LED_MODE); //LED_MODE ON
				}
				else // configuration mode
				{
					NextState = STATE_POT;
					GPIO_1_OUT &= ~(1<<LED_MODE); //LED_MODE OFF
				}
				break;
			}
			case STATE_LDR:
			{
				NextState = STATE_MODE;
				
				ldr_value = ADC_Read_Multiple_Poll(0, 16); //Read from ADC0 (LDR)
				if(ldr_value < SET_POINT)
				{
					GPIO_1_OUT |= (1<<LED_LIGHT); //LED_LIGHT ON
				}
				else
				{
					GPIO_1_OUT &= ~(1<<LED_LIGHT); //LED_LIGHT OFF
				}
				
				/*USART*/
				USART0_putString("SET_POINT value: ");
				utoa(SET_POINT, output, 10);
				USART0_putString(output);
				USART0_putString("\n\r");
				
				USART0_putString("LDR value: ");
				utoa(ldr_value, output, 10);
				USART0_putString(output);
				USART0_putString("\n\r");
				
				break;
			}
			case STATE_POT:
			{
				NextState = STATE_MODE;
				SET_POINT_COPY = ADC_Read_Multiple_Poll(1, 16); //Read from ADC1 (POT)
				
				/*USART*/
				USART0_putString("Pot value: ");
				utoa(SET_POINT_COPY, output, 10);
				USART0_putString(output);
				USART0_putString("\n\r");
				
				break;
			}
			
			default:
				NextState = STATE_MODE; 
			break;
		}
		
		CurrentState = NextState; //change to the next state
    }
}

