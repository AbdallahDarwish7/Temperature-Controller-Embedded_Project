/**
 * Created by abdallah drwesh on 6/7/21.
 */
#include "PWM.h"
#include "Timer.h"
#include "DIO.h"

static uint8 PWM_TimerId = 0;

void PWM_SetDutyCycle(float Percentage, uint8 PwmMode, uint8 PwmOutputCompareMode){
    DIO_ChannelDir(1, 3, 0xff);
    Timer_SetDutyCycle(PWM_TimerId, Percentage, PwmMode, PwmOutputCompareMode);
    Timer_Init(PWM_TimerId, PwmMode, PwmOutputCompareMode);
}

void PWM_Start(){
    Timer_Start(PWM_TimerId, TIMER0_PRESCALER_8);
}

void PWM_Stop(){
    Timer_Stop(PWM_TimerId);
}


