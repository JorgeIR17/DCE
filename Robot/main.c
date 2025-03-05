/*
 * SigueLineasV2.c
 *
 * Created: 05/03/2025 13:01:01
 * Author : Jorge
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "WHEELS.h"
#include "BUZZER.h"
#include "OPTO_SENSORS.h"


//---------  User data types definitions -------------
typedef enum {
	STATE_INIT,
	STATE_WAIT_BLACK,
	STATE_FOLLOW_LINE,
	STATE_STOP
} States_t;


int main(void)
{
	// ---------------------------------- SETUP ------------------------------
	
	uint16_t valor_sensor;
	uint16_t valores[5] = {0,0,0,0,0};
	
	// Initializes buzzer
	buzzerInit();
	
	// Initializes opto sensors
	sensors_init();
	
	// Initializes wheels
	setupWheels();
	

	// Make sure that the robot starts in STOP mode
	Robot_STOP();
	
	// Starts in STATE_INIT
	States_t currentState = STATE_INIT;
	States_t nextState = STATE_INIT;
	
	valor_sensor = check_IR_Sensor(IR2);	// Lectura descartada, por sincronizaci?n
	
	
	// ---------------------------------- LOOP ------------------------------
	while (1)
	{
		switch(currentState){
			case STATE_INIT:
			playSound_TMR(STARTING_SOUND, TICKS_1_sec);
			_delay_ms(1000);
			// Transition
			nextState = STATE_WAIT_BLACK;
			break;
			
			case STATE_WAIT_BLACK:
			readSensors(valores);
			// Transition
			if (valores[2] <= BLACK && valores[0] >= WHITE && valores[1] >= WHITE && valores[3] >= WHITE && valores[4] >= WHITE)
			nextState = STATE_FOLLOW_LINE;
			break;
			
			case STATE_FOLLOW_LINE:
			readSensors(valores);
			if (valores[2] <= BLACK && valores[1] >= WHITE && valores[3] >= WHITE) // Central negro y los de sus lados blancos --> FORWARD
			Robot_FWD(70, 70);
			if (valores[1] <= BLACK && valores[2] >= WHITE) // izquierda del central negro y central blanco --> GIRO IQUIERDA BRUSCO
			Robot_LEFT(15, 70);
			if (valores[3] <= BLACK && valores[2] >= WHITE) // derecha del central negro y central blanco --> GIRO DERECHA BRUSCO
			Robot_RIGHT(70, 15);
			if (valores[2] <= BLACK && valores[1] <= BLACK) // izquierda del central negro y central negro --> GIRO IQUIERDA SUAVE
			Robot_LEFT(30,60);
			if (valores[2] <= BLACK && valores[3] <= BLACK) // // derecha del central negro y central negro --> GIRO DERECHA SUAVE
			Robot_RIGHT(60, 30);
			
			// Transition
			if (valores[0] >= WHITE && valores[1] >= WHITE && valores[2] >= WHITE && valores[3] >= WHITE && valores[4] >= WHITE)
			nextState = STATE_STOP;
			
			_delay_ms(15);
			break;
			
			case STATE_STOP:
			Robot_STOP();
			_delay_ms(200);
			// Transition
			nextState = STATE_WAIT_BLACK;
			break;
			
			default: // default is STATE_WAIT_BLACK
			readSensors(valores);
			// Transition
			if (valores[2] <= BLACK && valores[0] >= WHITE && valores[1] >= WHITE && valores[3] >= WHITE && valores[4] >= WHITE)
			nextState = STATE_FOLLOW_LINE;
			break;
		}
		
		currentState = nextState;
	}
}





