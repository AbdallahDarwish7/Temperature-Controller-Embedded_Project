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


uint8* States[4] = {(uint8*)"STANDBY", (uint8*)"OPERATION", (uint8*)"NORMAL", (uint8*)"ERROR"};
uint8 numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
uint8 loop = (uint8)0;
uint8 count ;

void DisplayWelcomeScreen(uint8 times) {
    LCD_WriteChar(' ');
	count = times;
    LCD_WriteStringAt_xy((uint8)0, (uint8)0, (uint8*)"WELCOME");
    StartSoftwareAlarm((uint32) 100, &Shift_Right);
}

void Shift_Right(void) {
	LCD_Shift_R();
	loop++;
	if(loop > (uint8)9){
	    LCD_Shift_L();
        StartSoftwareAlarm((uint32) 100, &Shift_Left);
	} else{
        StartSoftwareAlarm((uint32) 100, &Shift_Right);
	}
}

void Shift_Left(void) {
	LCD_Shift_L();
	loop--;
	if(loop < (uint8)1){
        count--;
		if(count > (uint8)0){
            LCD_Shift_R();
            StartSoftwareAlarm((uint32) 100, &Shift_Right);
		}else{
			idle_screen();
		}
	} else{
        StartSoftwareAlarm((uint32) 100, &Shift_Left);
	}

}

void idle_screen(void){
	LCD_Clear();
    LCD_WriteChar(' ');
    LCD_WriteStringAt_xy((uint8)0, (uint8)0, (uint8*)"SET:25");
    LCD_WriteStringAt_xy((uint8)0, (uint8)10, (uint8*)"CRT:XX");
    LCD_WriteStringAt_xy((uint8)1, (uint8)0, (uint8*)"STATE:STANDBY");
}

void write_State(uint8 state){
    LCD_WriteStringAt_xy((uint8)1, (uint8)6, (uint8*)"          ");
    LCD_WriteStringAt_xy((uint8)1, (uint8)6, States[state]);
}

void write_CRT_Temp(uint8 crt_temp){
    LCD_WriteStringAt_xy((uint8)0, (uint8)14, (uint8*)"  ");
	uint8 first = (uint8)(crt_temp / (uint8)10);
	uint8 second = (uint8)(crt_temp % (uint8)10);
	uint8 temp[3] = {numbers[first], numbers[second], '\0'};
    LCD_WriteStringAt_xy((uint8)0, (uint8)14, temp);
}

void WriteSetTemp(uint8 set_temp) {
    LCD_WriteStringAt_xy((uint8)0, (uint8)4, (uint8*)"  ");
	uint8 firstset = (uint8)(set_temp / (uint8)10);
	uint8 secondset = (uint8)(set_temp % (uint8)10);
	uint8 tempset[3] = {numbers[firstset], numbers[secondset], '\0'};
    LCD_WriteStringAt_xy((uint8)0, (uint8)4, tempset);

}

void DisplayWelcomeScreenWrapper(void){
    DisplayWelcomeScreen(3U);
}
void Activate_LCD(void){
	LCD_Init();
    LCD_Callback = DisplayWelcomeScreenWrapper;
}
