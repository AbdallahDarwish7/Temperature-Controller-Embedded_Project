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

uint8 NumTimeShift = 1;
uint8 Index = 0;
void LCD_Shift_R(void){
    Delay_ms(500, LCD_Shift_R);
    LCD_Command(0x1c);
}
char* States[4] = {"STANDBY", "OPERATION", "NORMAL", "ERROR"};
char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
void display_Welcome_screen(uint8 times) {
	LCD_Char(' ');
	
	LCD_String_xy(0, 0,"WELCOME");
	/*while(times > 0){
		display_Welcome_once();
		times--;
	}
	idle_screen();
	_delay_ms(1000);
	write_Set_Temp(7);*/
    Delay_ms(500, LCD_Shift_R);
//    StartPeriodicDelay_ms(LCD_Shift_R);
}

void display_Welcome_once(void){
	uint8 loop = 0;

	while(loop < 9){
		LCD_Command(0x1c);
		_delay_ms(100);
		loop++;
	}
	while(loop >0){
		loop--;
		LCD_Command(0x18);
		_delay_ms(100);
	}
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