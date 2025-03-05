/*
 * OPTO_SENSORS.h
 *
 * Created: 06/05/2024 9:25:54
 *  Author: DCE
 */ 


#ifndef OPTO_SENSORS_H_
#define OPTO_SENSORS_H_

#include "ADC.h"

#define IR0 ADC7
#define IR1 ADC6
#define IR2 ADC5
#define IR3 ADC4
#define IR4 ADC1

#define WHITE 900
#define BLACK 600

uint16_t check_IR_Sensor(uint8_t IR_Number);

void readSensors(uint16_t sensors[]);

static inline void sensors_init()
{
    init_ADC(AVCC, ALIGN_RIGHT, PRESCALER_128);
}

#endif /* OPTO_SENSORS_H_ */