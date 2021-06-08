/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */

#include "typedefs.h"
#include "Scheduler.h"
#include "LCD_Manager.h"
#include "KeyPad.h"

int main(void) {

	/* test lcd keypad */
	//    test_KeyPad_Lcd();
	//    /* test pwd */
	//    float Percentage = 20;
	//    DIO_ChannelDir(1, 3, 0xff);
	//    Timer_Init(0, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
	//    PWM_SetDutyCycle(0, Percentage, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
	//    Timer_Start(0, TIMER0_PRESCALER_8);
	//DIO_ChannelDir(0, 0, 0xff);
	//DIO_ChannelDir(0, 1, 0xff);
	//DIO_ChannelDir(0, 2, 0xff);
	//PeriodicDelay_ms(100, ToggleBit0);
	//PeriodicDelay_ms(200, ToggleBit1);
	//PeriodicDelay_ms(400, ToggleBit2);
	//StartPeriodicDelay_ms(ToggleBit0);
	//StartPeriodicDelay_ms(ToggleBit1);
	//StartPeriodicDelay_ms(ToggleBit2);
	//    _delay_ms(8000);
	//    StopPeriodicDelay_ms(ToggleBit2);
	//    StopPeriodicDelay_ms(ToggleBit1);
	Initialize_LCD();
    KeyPad_Initialize();
	display_Welcome_screen(1);
	uint8 key = 0xff;
    Delay_ms(1000, get_set_Temp_wrapper);
	while(1){}
}