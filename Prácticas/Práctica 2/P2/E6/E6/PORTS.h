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
#define LED_MODE		DDD3
/*MCU Port where the LED is connected.*/
#define GPI001_OUT		PORTD
/*Pin of the port where the LED is connected.*/
#define LED				PORTD3

static inline void GPI0_init()
{
	//static: invisible outside of the file
	//inline: not called, copied into the file calling it instead
		GPI001 |=(1<<LED_MODE);
}

#endif /* PORTS_H_ */