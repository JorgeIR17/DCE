/*
 * PORTS.h
 *
 * Created: 19/02/2024 9:32:15
 *  Author: DCE
 */ 


#ifndef PORTS_H_
#define PORTS_H_

/*MCU Port where the LED is connected. Mode configuration register.*/
#define GPI001			DDRD
/*Pin of the port where the LED is connected. Configured as output.*/
#define LED1_MODE		DDD4

#define LED2_MODE		DDD5

#define LED3_MODE		DDD6

#define LED4_MODE		DDD7


#define BUTTON_MODE		DDD2
/*MCU Port where the LED is connected.*/
#define GPIO_1_OUT		PORTD

#define LED1_PIN		PORTD4

#define LED2_PIN		PORTD5

#define LED3_PIN		PORTD6

#define LED4_PIN		PORTD7

#define GPIO01_IN		PIND

#define BUTTON1			PORTD2

#define BUTTON2			PORTD3

static inline void GPIO_init()
{
	//static: invisible outside of the file
	//inline: not called, copied into the file calling it instead
		GPI001 |=(1<<LED1_MODE) | (1<<LED2_MODE) | (1<<LED3_MODE) | (1<<LED4_MODE);
		GPIO_1_OUT |=(1<<BUTTON1) | (1<<BUTTON2);
}

#endif /* PORTS_H_ */