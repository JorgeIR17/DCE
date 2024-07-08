/*
 * PORTS.h
 *
 * Created: 19/02/2024 9:32:15
 *  Author: DCE
 */ 


#ifndef PORTS_H_
#define PORTS_H_

/*We will write the set_point on 0x00*/
#define EEPROM_ADDRESS (uint8_t *) 0x00

#define PRODUCTION 0

#define CONFIGURATION 1

/*MCU Port where the LED is connected. Mode configuration register.*/
#define GPI001			DDRD
/*Pin of the port where the LED is connected. Configured as output.*/
#define LED1_MODE		DDD4

#define LED2_MODE		DDD5

#define LED_LIGHT_MODE		DDD6

#define LED_MODE_MODE		DDD7

/*MCU Port where the LED is connected.*/
#define GPIO_1_OUT		PORTD

#define LED_LIGHT		PORTD6

#define LED_MODE		PORTD7

#define GPIO01_IN		PIND

#define BUTTON_MODE		PORTD2

#define BUTTON_INTRO	PORTD3

static inline void GPIO_init()
{
	//static: invisible outside of the file
	//inline: not called, copied into the file calling it instead
		GPI001 |=(1<<LED_LIGHT_MODE) | (1<<LED_MODE_MODE);
		GPIO_1_OUT |=(1<<BUTTON_MODE) | (1<<BUTTON_INTRO);
}

#endif /* PORTS_H_ */