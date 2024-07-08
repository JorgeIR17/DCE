/*
 * main_b.c
 *
 * Created: 22/04/2024 10:17:11
 *  Author: DCE
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TMR1.h"



int main(void)
{
	TMR1_CTC_Init();
	TMR1_CTC_Set(7813); //~=500 ms
	TMR1_HW_toggleOC1A();
	
	TMR1_CTC_Start(DIV_CLK_1024);
	
	while (1)
	{
	}
}