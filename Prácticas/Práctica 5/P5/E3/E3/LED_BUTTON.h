#ifndef LED_BUTTON_H_
#define LED_BUTTON_H_

#include <stdbool.h>

#define LED_TOGGLE(ADDRESS,BIT)     ADDRESS ^= (1<<BIT)
#define LED_ON(ADDRESS,BIT)         ADDRESS |= (1<<BIT)
#define LED_OFF(ADDRESS,BIT)        ADDRESS &= ~(1<<BIT)
#define IS_PIN_ZERO(ADDRESS,BIT)    !(ADDRESS &(1<<BIT))    // Flag=0 --> TRUE
#define READ_BUTTON(ADDRESS,BIT)    (ADDRESS &(1<<BIT))     // Check the button state
#define BUTTON_PRESSED              0
#define BUTTON_NOT_PRESSED          1
#define ALREADY_FINISHED_PRESSING   1
#define NOT_FINISHED_PRESSING       0

//--------- PARAMETERS ------------------------------------------
/// 1. Time in ms the MCU waits for the bouncing in the pushbutton.
#define DEBOUNCE_TIME 10
#define BLINK_TIME 100

//--------- Data type definition for DEBOUNCE FSM -------------
typedef enum {
    STATE_START,
    STATE_TIMER,
    STATE_RELEASE,
    STATE_DEBOUNCED,
    STATE_EXIT_TIMER
} debounceStates_t;
//------------------------------------------------------

#endif /* LED_BUTTON_H_ */