/*
 * WHEELS.c
 *
 * Created: 13/05/2024 13:24:15
 *  Author: Jorge
 */ 

#include "WHEELS.h"

void Robot_FWD(uint8_t speedLeft, uint8_t speedRight)
{
	TMR4_PWM_Phase_Start(TMR4_DIV_CLK_64);
	
	// Forward
	PORTE &= ~(1<<EN2);
	PORTD &= ~(1<<EN1);
	TMR4_PWM_Phase_Duty(speedLeft,speedRight);
}


void Robot_BWD(uint8_t speedLeft, uint8_t speedRight)
{
	TMR4_PWM_Phase_Start(TMR4_DIV_CLK_64);
	
	// Backward
	PORTE |= (1<<EN2);
	PORTD |= (1<<EN1);
	TMR4_PWM_Phase_Duty(speedLeft,speedRight);
}


void Robot_STOP()
{
	TMR4_PWM_Phase_Stop();
}


void Robot_RIGHT(uint8_t speedLeft, uint8_t speedRight)
{
	TMR4_PWM_Phase_Start(TMR4_DIV_CLK_64);
	
	// Derecha
	PORTE &= ~(1<<EN2);
	PORTD &= ~(1<<EN1);
	TMR4_PWM_Phase_Duty(speedLeft,speedRight);
}


void Robot_LEFT(uint8_t speedLeft, uint8_t speedRight)
{
	TMR4_PWM_Phase_Start(TMR4_DIV_CLK_64);
	
	// Izquierda
	PORTE &= ~(1<<EN2);
	PORTD &= ~(1<<EN1);
	TMR4_PWM_Phase_Duty(speedLeft,speedRight);
}

void Robot_Test()
{
	Robot_FWD(135, 135);
	_delay_ms(1000);
	
	Robot_BWD(135, 135);
	_delay_ms(1000);
	
	Robot_LEFT(135, 35);
	_delay_ms(125);
	
	Robot_RIGHT(35, 135);
	_delay_ms(125);
}