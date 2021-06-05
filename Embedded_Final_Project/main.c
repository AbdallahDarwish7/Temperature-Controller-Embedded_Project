/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */

#include "Timer.h"
#include "DIO.h"

int main(void) {
    float Percentage = 20;
    DIO_ChannelDir(1, 3, 0xff);
    Timer_Init(0, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
    PWM_SetDutyCycle(0, Percentage, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
    Timer_Start(0, TIMER0_PRESCALER_8);
    while (1) {}
}

