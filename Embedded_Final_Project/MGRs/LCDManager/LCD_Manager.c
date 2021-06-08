/*
 * LCD_Manager.c
 *
 * Created: 6/6/2021 6:45:32 PM
 *  Author: river
 */ 
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include "LCD_Manager.h"
#include "LCD_Manager_cfg.h"
#include "Scheduler.h"
#include "LCD.h"
#include "typedefs.h"
#include "KeyPad.h"


char* States[4] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
uint8 loop = 0;
uint8 count ;
void display_Welcome_screen(uint8 times) {
	LCD_Char(' ');
	count = times;
	LCD_String_xy(0, 0,"WELCOME");
	
	display_Welcome_once();

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
	if(loop < 1){
		StopPeriodicDelay_ms(Shift_Left);
		if(count > 0){
			count--;
			StartPeriodicDelay_ms(Shift_Right);
			
		}else{
			idle_screen();
		}
	}
}
void display_Welcome_once(void){
	PeriodicDelay_ms(100,Shift_Right);
	PeriodicDelay_ms(100, Shift_Left);
	StartPeriodicDelay_ms(Shift_Right);

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
	uint8 first = crt_temp / 10;
	uint8 second = crt_temp % 10;
	
	char temp[2] = {numbers[first], numbers[second]};
	LCD_String_xy(0,14,temp);
	
}

void write_Set_Temp(uint8 set_temp) {
	LCD_String_xy(0,4,"  ");
	uint8 first = set_temp / 10;
	uint8 second = set_temp % 10;
	
	char temp[2] = {numbers[first], numbers[second]};
	LCD_String_xy(0, 4, temp);
	LCD_String_xy(0,10,"CRT");
}

void Initialize_LCD(){
	LCD_Init();
}