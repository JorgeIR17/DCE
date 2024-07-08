#define AVCC 1
#define AREF 0
#define ALIGN_LEFT 1
#define ALIGN_RIGHT 0
#define PRESCALER_128 7

#ifndef ADC_H_
#define ADC_H_

static inline void init_ADC(uint8_t VREF, uint8_t ALIGN, uint8_t PRESCALER)
{
    ADMUX &= (0b00110000); //DELETE
    ADMUX |= (VREF << REFS0); // AVCC
    ADMUX |= (ALIGN << ADLAR); //ALIGNMENT
    ADCSRA &= (0b00000000);
    ADCSRA |= (PRESCALER << ADPS0); //PRESCALER 125KHz
    ADCSRA |= (1 << ADEN); //ENABLE ADEN
}
static inline void ADC_select_channel(uint16_t channel)
{
    ADMUX &= (0b11110000);
    ADMUX |= (channel << MUX0);
    ADCSRA |= (1 << ADSC);
}

static inline void ADC_enableInt()
{
    ADCSRA |= (1<<ADIE);
}
static inline void ADC_disableInt()
{
    ADCSRA &= ~(1<<ADIE);
}

static inline void ADC_START(){
	ADCSRA |= (1<<ADSC);
}

uint16_t ADC_Read_Single_Poll(uint8_t channel);

uint16_t ADC_Read_Multiple_Poll(uint8_t channel, uint8_t times);


#endif /* ADC_H_ */