/*
 * LCD_Manager.c
 *
 * Created: 6/6/2021 6:45:32 PM
 *  Author: river
 */ 
#include "LCD.h"
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include "LCD_Manager_cfg.h"
#include "LCD_Manager.h"
#include "Scheduler.h"
#include <string.h>

char* States[4] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
uint8 loop =0;
uint8 count ;
void display_Welcome_screen(uint8 times) {
	LCD_Char(' ');
	count = times;
	LCD_String_xy(0, 0,"WELCOME");
	while(times > 0){
		display_Welcome_once();
		//Delay_ms(100,display_Welcome_once);
		times = 0;
	}
	//Delay_ms(100*3*18, idle_screen);
}
void Shift_Right(void) {
	LCD_Shift_R();
	loop++;
	if(loop > 9){
		StopPeriodicDelay_ms(Shift_Right);
		StartPeriodicDelay_ms(Shift_Left);
	}
}
void Shift_Left(void) {
	LCD_Shift_L();
	loop--;
	if(loop < 2){
		StopPeriodicDelay_ms(Shift_Left);
		if(count > 0){
			count--;
			StartPeriodicDelay_ms(Shift_Right);
			
		}
	}
}
void display_Welcome_once(void){
	PeriodicDelay_ms(100,Shift_Right);
	PeriodicDelay_ms(100, Shift_Left);

	/*
	while(loop < 9){
		LCD_Command(0x1c);
		_delay_ms(100);
		loop++;
	}
	uint8 delay = loop - 1;
	while(loop >0){
		loop--;
		Delay_ms(100 * delay, LCD_Shift_L);
		delay++;
		LCD_Command(0x18);
		_delay_ms(100);
	}*/
}

void idle_screen(void){
	
	LCD_Clear();
	LCD_Char(' ');
	LCD_String_xy(0,0,"SET:25");
	LCD_String_xy(0,10,"CRT:YY");
	LCD_String_xy(1,0,"STATE:STANDBY");
}

void write_State(STATES_ConfigParamType state){
	LCD_String_xy(1,6,"          ");
	LCD_String_xy(1,6,States[state]);
}

void write_CRT_Temp(uint8 crt_temp){
	LCD_String_xy(0,14,"  ");
	uint8 first = crt_temp / 100;
	uint8 second = crt_temp % 100;
	
	char temp[2] = {numbers[first], numbers[second]};
	LCD_String_xy(0,14,&temp);
	
}

void write_Set_Temp(uint8 set_temp) {
	LCD_String_xy(0,4,"  ");
	uint8 first = set_temp / 10;
	uint8 second = set_temp % 10;
	
	char temp[2] = {numbers[first], numbers[second]};
	LCD_String_xy(0,4,&temp);
	LCD_String_xy(0,10,"CRT");
}

void Initialize_LCD(){
	LCD_Init();
}