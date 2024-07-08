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



#define BUTTON_MODE		DDD2
/*MCU Port where the LED is connected.*/
#define GPIO_1_OUT		PORTD


#define GPIO01_IN		PIND

#define BUTTON			PORTD2

static inline void GPIO_init()
{
	//static: invisible outside of the file
	//inline: not called, copied into the file calling it instead
		GPI001 |= (1<<DDD4) |  (1<<DDD5) |  (1<<DDD6) |  (1<<DDD7);
		GPIO_1_OUT |=(1<<BUTTON);
}

#endif /* PORTS_H_ */