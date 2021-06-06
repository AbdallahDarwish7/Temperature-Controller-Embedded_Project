/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */

#include "Timer.h"
#include "DIO.h"
#include "KeyPad.h"

uint8 data = 0xff;
void ToggleBit(void) {
    DIO_ChannelWrite(0, 0, data);
    data ^= 0xff;
}
int main(void) {
    /* test lcd keypad */
//    test_KeyPad_Lcd();
//    /* test pwd */
//    float Percentage = 20;
//    DIO_ChannelDir(1, 3, 0xff);
//    Timer_Init(0, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
//    PWM_SetDutyCycle(0, Percentage, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
//    Timer_Start(0, TIMER0_PRESCALER_8);
    DIO_ChannelDir(0, 0, 0xff);
    Timer_Delay(2, 0, ToggleBit);
    while (1) {}
}
