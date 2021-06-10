/*
 * LCD_Manager.c
 *
 * Created: 6/6/2021 6:45:32 PM
 *  Author: river
 */ 
#include "Display_MGR.h"
#include "Scheduler.h"
#include "LCD.h"
#include "typedefs.h"
#include "KeyPad.h"
#include "Scheduler.h"


uint8* States[4] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
uint8 numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
uint8 loop = (uint8)0;
uint8 count ;

void display_Welcome_screen(uint8 times) {
    LCD_WriteChar(' ');
	count = times;
    LCD_WriteStringAt_xy((uint8)0, (uint8)0, "WELCOME");
    Delay_ms((uint32)100, &Shift_Right);
}

void Shift_Right(void) {
	LCD_Shift_R();
	loop++;
	if(loop > (uint8)9){
	    LCD_Shift_L();
        Delay_ms((uint32)100, &Shift_Left);
	} else{
        Delay_ms((uint32)100, &Shift_Right);
	}
}

void Shift_Left(void) {
	LCD_Shift_L();
	loop--;
	if(loop < (uint8)1){
        count--;
		if(count > (uint8)0){
            LCD_Shift_R();
            Delay_ms((uint32)100, &Shift_Right);
		}else{
			idle_screen();
		}
	} else{
        Delay_ms((uint32)100, &Shift_Left);
	}

}

void display_Welcome_once(void){
	PeriodicDelay_ms((int16)100,&Shift_Right);
	PeriodicDelay_ms((int16)100, &Shift_Left);
	StartPeriodicDelay_ms(&Shift_Right);
}

void idle_screen(void){
	LCD_Clear();
    LCD_WriteChar(' ');
    LCD_WriteStringAt_xy((uint8)0, (uint8)0, "SET:25");
    LCD_WriteStringAt_xy((uint8)0, (uint8)10, "CRT:YY");
    LCD_WriteStringAt_xy((uint8)1, (uint8)0, "STATE:STANDBY");
}

void write_State(uint8 state){
    LCD_WriteStringAt_xy((uint8)1, (uint8)6, "          ");
    LCD_WriteStringAt_xy((uint8)1, (uint8)6, States[state]);
}

void write_CRT_Temp(uint8 crt_temp){
    LCD_WriteStringAt_xy((uint8)0, (uint8)14, "  ");
	uint8 first = (uint8)(crt_temp / (uint8)10);
	uint8 second = (uint8)(crt_temp % (uint8)10);
	uint8 temp[3] = {numbers[first], numbers[second], '\0'};
    LCD_WriteStringAt_xy((uint8)0, (uint8)14, temp);
}

void WriteSetTemp(uint8 set_temp) {
    LCD_WriteStringAt_xy((uint8)0, (uint8)4, "  ");
	uint8 firstset = (uint8)(set_temp / (uint8)10);
	uint8 secondset = (uint8)(set_temp % (uint8)10);
	uint8 tempset[3] = {numbers[firstset], numbers[secondset], '\0'};
    LCD_WriteStringAt_xy((uint8)0, (uint8)4, tempset);

}

void Activate_LCD(void){
	LCD_Init();
}
