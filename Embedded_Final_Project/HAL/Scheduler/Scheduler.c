/**
 * Created by abdallah drwesh on 6/5/21.
 */
#include "Scheduler.h"
#include "Timer.h"
#include "Macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_ONE_SHOT_CALLBACKS 8U
#define NUM_PERIODIC_CALLBACKS 3U

#define PERIODIC_ON 1U
#define PERIODIC_OFF 0U

VoidCallback OneShotCallbacks[NUM_ONE_SHOT_CALLBACKS];
uint32 OneShotCounts[NUM_ONE_SHOT_CALLBACKS];
static uint8 TimerIdForOneShotDelay = 2;
VoidCallback TempCallback;

VoidCallback PeriodicCallbacks[NUM_PERIODIC_CALLBACKS] = {NULL, NULL, NULL};
uint32 PeriodicTimerOverflow[NUM_PERIODIC_CALLBACKS];
uint32 PeriodicCounts[NUM_PERIODIC_CALLBACKS];
uint8 PeriodicState[NUM_PERIODIC_CALLBACKS];
static uint8 TimerIdPeriodicDelay = 1;

void Delay_ms(uint32 delay_ms, VoidCallback callback) {
    uint8 timerIsRunning = Timer_Is_Running(TimerIdForOneShotDelay);
    uint8 Loop;
    if (!timerIsRunning) {
        for (Loop = 0U; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
            OneShotCallbacks[Loop] = NULL;
        }
    }
    for (Loop = 0U; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
        if (OneShotCallbacks[Loop] == NULL) {
            break;
        }
    }
    if (Loop < NUM_ONE_SHOT_CALLBACKS) {
        OneShotCallbacks[Loop] = callback;
        OneShotCounts[Loop] = (uint32)(delay_ms / 25U);
    }
    /*25ms*/
    if (!timerIsRunning) {
        Timer_Init(TimerIdForOneShotDelay, TIMER_CTC_MODE, TIMER_DISCONCTED_COM);
        /* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
        OCR2 = 194U;
        /* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
        SET_BIT(TIMSK, OCIE2);
        sei();
        Timer_Start(TimerIdForOneShotDelay, TIMER2_PRESCALER_1024);
    }
}

void DeleteDelay_ms(VoidCallback callback) {
    cli();
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 Loop;
    for (Loop = 0U; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
        if (OneShotCallbacks[Loop] == callback) {
            OneShotCallbacks[Loop] = NULL;
        }
    }
    sei();
}

ISR(TIMER2_COMP_vect) {
    /* JUSTIFICATION: local variables for the same meaning */
    uint8 Loop;
    uint8 isThereCallback = 0;
    for (Loop = 0U; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
        if (OneShotCallbacks[Loop] != NULL) {
            OneShotCounts[Loop]--;
            if (OneShotCounts[Loop] == 0U) {
                TempCallback = OneShotCallbacks[Loop];
                OneShotCallbacks[Loop] = NULL;
                TempCallback();
            }
            isThereCallback = 1U;
        }
    }
    if (!isThereCallback) {
        /* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
        CLEAR_BIT(TIMSK, OCIE0);
        Timer_Stop(TimerIdForOneShotDelay);
    }
}

void PeriodicDelay_ms(uint32 delay_ms, VoidCallback callback) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 timerIsRunning = Timer_Is_Running(TimerIdPeriodicDelay);
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 Loop;
    for (Loop = 0U; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
        if (PeriodicCallbacks[Loop] == NULL) {
            break;
        }
    }
    if (Loop < NUM_PERIODIC_CALLBACKS) {
        PeriodicCallbacks[Loop] = callback;
        PeriodicTimerOverflow[Loop] = (uint32)(delay_ms / 100U);
        PeriodicCounts[Loop] = PeriodicTimerOverflow[Loop];
    }
    /* 100ms */
    if (!timerIsRunning) {
        Timer_Init(TimerIdPeriodicDelay, TIMER_CTC_MODE, TIMER_DISCONCTED_COM);
        /* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
        OCR1A = 780U;
    }
}

void StartPeriodicDelay_ms(VoidCallback callback) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 Loop;
    for (Loop = 0U; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
        if (PeriodicCallbacks[Loop] == callback) {
            PeriodicState[Loop] = PERIODIC_ON;
            if (!Timer_Is_Running(TimerIdPeriodicDelay)) {
                /* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
                SET_BIT(TIMSK, OCIE1A);
                sei();
                Timer_Start(TimerIdPeriodicDelay, TIMER1_PRESCALER_1024);
            }
            break;
        }
    }
}

void StopPeriodicDelay_ms(VoidCallback callback) {
    cli();
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 Loop;
    for (Loop = 0U; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
        if (PeriodicCallbacks[Loop] == callback) {
            PeriodicState[Loop] = PERIODIC_OFF;
            PeriodicCounts[Loop] = PeriodicTimerOverflow[Loop];
            break;
        }
    }
    sei();
}

ISR(TIMER1_COMPA_vect) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 Loop;
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 isThereCallback = 0;
    for (Loop = 0U; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
        if ((PeriodicCallbacks[Loop] != NULL) && (PeriodicState[Loop] == PERIODIC_ON)) {
            PeriodicCounts[Loop]--;
            if (PeriodicCounts[Loop] == 0U) {
                PeriodicCallbacks[Loop]();
                PeriodicCounts[Loop] = PeriodicTimerOverflow[Loop];
            }
            isThereCallback = 1U;
        }
    }
    if (!isThereCallback) {
        /* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
        CLEAR_BIT(TIMSK, OCIE1A);
        Timer_Stop(TimerIdPeriodicDelay);
    }
}

void DeletePeriodicDelay_ms(VoidCallback callback) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 Loop;
    for (Loop = 0U; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
        if (PeriodicCallbacks[Loop] == callback) {
            PeriodicCallbacks[Loop] = NULL;
        }
    }
}
