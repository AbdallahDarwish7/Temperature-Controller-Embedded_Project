/**
 * Created by abdallah drwesh on 6/5/21.
 */
#include "Scheduler.h"
#include "Timer.h"
#include "Macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_ONE_SHOT_CALLBACKS 3U
#define NUM_PERIODIC_CALLBACKS 3U

VoidCallback OneShotCallbacks[NUM_ONE_SHOT_CALLBACKS];
uint32 OneShotTimerOverflow[NUM_ONE_SHOT_CALLBACKS];
uint32 OneShotCounts[NUM_ONE_SHOT_CALLBACKS];
static uint8 TimerIdForOneShotDelay = 2;

VoidCallback PeriodicCallbacks[NUM_ONE_SHOT_CALLBACKS];
uint32 PeriodicTimerOverflow[NUM_ONE_SHOT_CALLBACKS];
uint16 PeriodicCounts[NUM_ONE_SHOT_CALLBACKS];
static uint8 TimerIdPeriodicDelay = 1;

void Delay_ms(uint32 Delay_ms, VoidCallback callback) {
    uint8 timerIsRunning = Timer_Is_Running(TimerIdForOneShotDelay);
    uint8 Loop;
    if (!timerIsRunning) {
        for (Loop = 0; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
            OneShotCallbacks[Loop] = NULL;
        }
    }
    for (Loop = 0; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
        if (OneShotCallbacks[Loop] == NULL) {
            break;
        }
    }
    if (Loop < NUM_ONE_SHOT_CALLBACKS) {
        OneShotCallbacks[Loop] = callback;
        OneShotTimerOverflow[Loop] = 10 * Delay_ms;
        OneShotCounts[Loop] = 10 * Delay_ms;
    }
    // 100us
    if (!timerIsRunning) {
        Timer_Init(TimerIdForOneShotDelay, TIMER_CTC_MODE, TIMER_DISCONCTED_COM);
        OCR2 = 99;
        SET_BIT(TIMSK, OCIE2);
        sei();
        Timer_Start(TimerIdForOneShotDelay, TIMER2_PRESCALER_8);
    }
}

ISR(TIMER2_COMP_vect) {
    uint8 Loop;
    uint8 isThereCallback = 0;
    for (Loop = 0; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
        if (OneShotCallbacks[Loop] != NULL) {
            OneShotCounts[Loop]--;
            if (OneShotCounts[Loop] == 0U) {
                OneShotCallbacks[Loop]();
                OneShotCallbacks[Loop] = NULL;
//                OneShotCounts[Loop] = OneShotTimerOverflow[Loop];
            }
            isThereCallback = 1;
        }
    }
    if (!isThereCallback) {
        CLEAR_BIT(TIMSK, OCIE0);
        Timer_Stop(TimerIdForOneShotDelay);
    }
}

void Periodic_Delay_ms(int16 Delay_ms, VoidCallback callback) {
    uint8 timerIsRunning = Timer_Is_Running(TimerIdPeriodicDelay);
    uint8 Loop;
    if (!timerIsRunning) {
        for (Loop = 0; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
            PeriodicCallbacks[Loop] = NULL;
        }
    }
    for (Loop = 0; Loop < NUM_PERIODIC_CALLBACKS; Loop++) {
        if (PeriodicCallbacks[Loop] == NULL) {
            break;
        }
    }
    if (Loop < NUM_PERIODIC_CALLBACKS) {
        PeriodicCallbacks[Loop] = callback;
        PeriodicTimerOverflow[Loop] = Delay_ms / 100;
        PeriodicCounts[Loop] = Delay_ms / 100;
    }
    // 100ms
    if (!timerIsRunning) {
        Timer_Init(TimerIdPeriodicDelay, TIMER_CTC_MODE, TIMER_DISCONCTED_COM);
        OCR1A = 780;
        SET_BIT(TIMSK, OCIE1A);
        sei();
        Timer_Start(TimerIdPeriodicDelay, TIMER1_PRESCALER_1024);
    }
}

ISR(TIMER1_COMPA_vect) {
    uint8 Loop;
    uint8 isThereCallback = 0;
    for (Loop = 0; Loop < NUM_ONE_SHOT_CALLBACKS; Loop++) {
        if (PeriodicCallbacks[Loop] != NULL) {
            PeriodicCounts[Loop]--;
            if (PeriodicCounts[Loop] == NULL) {
                PeriodicCallbacks[Loop]();
                PeriodicCounts[Loop] = PeriodicTimerOverflow[Loop];
            }
            isThereCallback = 1;
        }
    }
    if (!isThereCallback) {
        CLEAR_BIT(TIMSK, OCIE1A);
        Timer_Stop(TimerIdPeriodicDelay);
    }
}