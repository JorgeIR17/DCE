/*
 * OPTO_SENSORS.c
 *
 * Created: 06/05/2024 9:29:11
 *  Author: DCE
 */ 

#include "OPTO_SENSORS.h"

uint16_t check_IR_Sensor(uint8_t IR_Number)
{
	return ADC_Read_Single_Poll(IR_Number);
}

void readSensors(uint16_t sensors[])
{
	sensors[0] = check_IR_Sensor(IR0);
	sensors[1] = check_IR_Sensor(IR1);
	sensors[2] = check_IR_Sensor(IR2);
	sensors[3] = check_IR_Sensor(IR3);
	sensors[4] = check_IR_Sensor(IR4);
}