/*
 * WHEELS.h
 *
 * Created: 13/05/2024 13:24:05
 *  Author: Jorge
 */ 


#ifndef WHEELS_H_
#define WHEELS_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include "TMR4.h"

#define EN1 PORTD6
#define EN2 PORTE6

void Robot_FWD(uint8_t speedLeft, uint8_t speedRight);

void Robot_BWD(uint8_t speedLeft, uint8_t speedRight);

void Robot_STOP();

void Robot_RIGHT(uint8_t speedLeft, uint8_t speedRight);

void Robot_LEFT(uint8_t speedLeft, uint8_t speedRight);

void Robot_Test();

static inline void setupWheels()
{
	DDRE |= (1<<EN2);
	DDRD |= (1<<EN1);
	
	TMR4_PWM_Phase_Init();
}

#endif /* WHEELS_H_ */