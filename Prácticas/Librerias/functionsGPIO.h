#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "LED_BUTTON.h"

#ifndef FUNCTIONSGPIO_H_
#define FUNCTIONSGPIO_H_

int GPIO_read(uint8_t Port, uint8_t Button_Pin);

#endif

#include "functionsGPIO.h"

int GPIO_read(uint8_t Port, uint8_t Button_Pin)
{
    ///------------------------------------------------------------
    /// 1. Check the EVENT in each iteration
    int finished = NOT_FINISHED_PRESSING;
    static debounceStates_t currentState = STATE_START;
    static debounceStates_t nextState = STATE_START;
    /// The value for "currentState" is preserved. (Static variable)
    ///-------------------------------------------------------------
    bool isButtonPressed = READ_BUTTON(Port,Button_Pin);
    //-----------------------------------------------------------
    /// 2. Set the TRANSITIONS based upon events
    ///------------------------------------------------------------
    switch(currentState)
    {
    ///------------------------------------------------------------
        case STATE_START:
        //-------------------------------------------------------
        // 2.1. When the pushbutton is pressed then...
            if (isButtonPressed==BUTTON_PRESSED)
            {
            nextState=STATE_TIMER;
            }
        break;
        //------------------------------------------------------------
        case STATE_TIMER:
        //------------------------------------------------------------
        // 2.2. When the debouncing time finishes goes to release
            nextState=STATE_RELEASE;
        break;
        ///------------------------------------------------------------
        case STATE_RELEASE:
        //------------------------------------------------------------
        // 2.3. Wait until the push is released (HIGH), then...
            if (isButtonPressed==BUTTON_NOT_PRESSED)
            {
                nextState=STATE_DEBOUNCED;
            }
        break;
        ///------------------------------------------------------------
        case STATE_DEBOUNCED:
        ///------------------------------------------------------------
        // 2.4. The change takes place when the debouncing time finishes
            nextState=STATE_EXIT_TIMER;
        break;
        case STATE_EXIT_TIMER:
        ///------------------------------------------------------------
        // 2.5.
            nextState=STATE_START;
        break;
        ///------------------------------------------------------------
        default:
        ///------------------------------------------------------------
            nextState=STATE_START;
        break;
    } // Close Switch-Transitions
    /// 3. Set the OUTPUTS in every state. Nothing to do in any state but the
    /// "STATE_DEBOUNCED" one.
    ///-------------------------------------------------------------------------
    switch (currentState)
    {
    ///------------------------------------------------------------
        case STATE_START:
        break;
        ///------------------------------------------------------------
        case STATE_TIMER:
            _delay_ms(DEBOUNCE_TIME);
        break;
        ///------------------------------------------------------------
        case STATE_RELEASE:
        break;
        ///------------------------------------------------------------
        case STATE_DEBOUNCED:
        break;
        ///------------------------------------------------------------
        case STATE_EXIT_TIMER:
        ///------------------------------------------------------------
            _delay_ms(DEBOUNCE_TIME);
            finished = ALREADY_FINISHED_PRESSING;
        break;
        default:
        break;
    ///------------------------------------------------------------
    } // Close Switch-Outputs
    //--------------------------------------------------------------------------
    // 4. UPDATE state
    currentState=nextState;
    return finished;
    //--------------------------------------------------------------------------
}
