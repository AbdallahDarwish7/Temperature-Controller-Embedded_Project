/**
 * Created by abdallah drwesh on 6/2/21.
 */

#ifndef FINAL_PROJECT_TIMER_H
#define FINAL_PROJECT_TIMER_H

#include "typedefs.h"

#define NUM_TIMERS ((uint8) 3U)
#define TIMER_NORMAL_MODE ((uint8) 0U)
#define TIMER_CTC_MODE ((uint8) 1U)
#define TIMER_PWD_PHASE_CORRECT_MODE ((uint8) 2U)
#define TIMER_PWD_FAST_MODE ((uint8) 3U)

#define TIMER_DISCONCTED_COM ((uint8) 0U)
#define TIMER_NON_INVERTED_COM ((uint8) 1U)
#define TIMER_INVERTED_COM ((uint8) 2U)

void Timer_Init(uint8 TimerId, uint8 TimerMode, uint8 TimerCom);

void Timer_Start(uint8 TimerId, uint16 TimerPreScaler);

void PWM_SetDutyCycle(uint8 TimerId, float Percentage, uint8 TimerMode, uint8 TimerCom);

void Timer_Stop(uint8 TimerId);

#define TIMER0_PRESCALER_1 ((uint16) 1U)
#define TIMER0_PRESCALER_8 ((uint16) 8U)
#define TIMER0_PRESCALER_64 ((uint16) 64U)
#define TIMER0_PRESCALER_256 ((uint16) 256U)
#define TIMER0_PRESCALER_1024 ((uint16) 1042U)

#define TIMER1_PRESCALER_1 ((uint16) 1U)
#define TIMER1_PRESCALER_8 ((uint16) 8U)
#define TIMER1_PRESCALER_64 ((uint16) 64U)
#define TIMER1_PRESCALER_256 ((uint16) 256U)
#define TIMER1_PRESCALER_1024 ((uint16) 1042U)

#define TIMER2_PRESCALER_1 ((uint16) 1U)
#define TIMER2_PRESCALER_8 ((uint16) 8U)
#define TIMER2_PRESCALER_32 ((uint16) 8U)
#define TIMER2_PRESCALER_64 ((uint16) 64U)
#define TIMER2_PRESCALER_128 ((uint16) 128U)
#define TIMER2_PRESCALER_256 ((uint16) 256U)
#define TIMER2_PRESCALER_1024 ((uint16) 1042U)
#endif //FINAL_PROJECT_TIMER_H
