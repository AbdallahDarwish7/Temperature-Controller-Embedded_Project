/*
 * CFile1.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */ 



#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include "DIO.h"
#include "DIO_Cfg.h"

#include "LCD.h"
#include "LCD_Cfg.h"

#include "Scheduler.h"
uint8 data_global;
uint8 CheckBit(uint8 Data, uint8 bitNum) {
	uint8 result ;
	uint8 mask = DIO_ConfigParam[LCD_ConfigParam.DataPortId][LCD_ConfigParam.DataPinsChannel[bitNum]].PortMask;
	if (Data & mask){
		result = 0xff;
		} else {
		result = 0x00;
	}
	return result;
}

void LCD_Write_Upper(uint8 char_data) {
	char_data = char_data & 0xF0;
	uint8 loop;
	uint8 data;
	for (loop = (uint8) 0; loop < LCD_NUM_OF_DATA_PINS; loop++)
	{
		data = CheckBit(char_data, loop);
		DIO_ChannelWrite(LCD_ConfigParam.DataPortId,LCD_ConfigParam.DataPinsChannel[loop],  data);
	}
}

void LCD_Write_Lower(uint8 char_data) {
	char_data = char_data << 4;
	uint8 loop;
	uint8 data;
	for (loop = (uint8) 0; loop < LCD_NUM_OF_DATA_PINS; loop++)
	{
		data = CheckBit(char_data, loop);
		DIO_ChannelWrite(LCD_ConfigParam.DataPortId,LCD_ConfigParam.DataPinsChannel[loop],  data);
	}
}

void LCD_RS_Command() {
	DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RSPinChannel, 0x00);
}

void LCD_RS_Reg() {
	DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RSPinChannel, 0xff);
}

void LCD_Read_Operation() {
	DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RWPinChannel, 0xff);
}

void LCD_Write_Operation() {
	DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RWPinChannel, 0x00);
}

void LCD_Enable() {
	DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.EnablePinChannel, 0xff);
}

void LCD_Disable() {
	DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.EnablePinChannel, 0x00);
}

void LCD_Command(uint8 cmnd)
{
	data_global = cmnd;
	LCD_Write_Upper(cmnd) ;
	LCD_RS_Command();	/* RS=0 command reg. */
	LCD_Write_Operation();	/* RW=0 Write operation */
	LCD_Enable();	/* Enable pulse */
	_delay_us(1);
	LCD_Disable();
	_delay_us(200);
	//Delay_ms(1, LCD_Write_Lower);
	LCD_Write_Lower(cmnd);
	LCD_RS_Command();	/* RS=0 command reg. */
	LCD_Write_Operation();	/* RW=0 Write operation */
	LCD_Enable();	/* Enable pulse */
	_delay_us(1);
	LCD_Disable();
	_delay_us(2);
}

void lower_Command(void){
	LCD_Write_Lower(data_global);
	LCD_RS_Reg();	/* RS=0 command reg. */
	LCD_Write_Operation();	/* RW=0 Write operation */
	LCD_Enable();	/* Enable pulse */
	_delay_us(1);
	LCD_Disable();
	_delay_us(2);
}
void LCD_Char (uint8 char_data)  /* LCD data0 write function */
{
	data_global = char_data;
	LCD_Write_Upper(char_data);
	LCD_RS_Reg();	/* RS=0 command reg. */
	LCD_Write_Operation();	/* RW=0 Write operation */
	LCD_Enable();	/* Enable pulse */
	_delay_us(1);
	LCD_Disable();
	_delay_us(200);			/* Data write delay */
	LCD_Write_Lower(char_data);
	LCD_RS_Reg();	/* RS=0 command reg. */
	LCD_Write_Operation();	/* RW=0 Write operation */
	LCD_Enable();	/* Enable pulse */
	_delay_us(1);
	LCD_Disable();
	_delay_us(2);
}

void LCD_Init_Delay(void) {
	LCD_Command (0X02);
	LCD_Command (0x28);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* clear display */
	_delay_us(2);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	DIO_Init(2);
	DIO_Init(3);
	//Delay_ms(20,LCD_Init_Delay);		/* LCD Power ON delay always >15ms */
	_delay_ms(20);
	LCD_Command (0X02);
	LCD_Command (0x28);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* clear display */
	_delay_us(2);
}


void LCD_String (uint8 *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char ((uint8)str[i]);
	}
}

void LCD_String_xy (uint8 row, uint8 pos, uint8 *str)  /* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
}

void LCD_NewLine()
{
	LCD_Command (0xc0);		/* clear display */
}

void LCD_Shift_R(void){
	LCD_Command(0x1c);
}

void LCD_Shift_L(void){
	LCD_Command(0x18);
}

void LCD_Custom_Char (uint8 loc, uint8 *msg)
{
	uint8 i;
	if(loc<8)
	{
		LCD_Command (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_Char(msg[i]);
	}
}

void test_LCD(void) {
	unsigned char loop;

	uint8 Characters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

	DIO_Init(2);
	DIO_Init(3);
	LCD_Init();
	LCD_Command(0x80);
	LCD_String(" ");
	LCD_String_xy(0, (uint8)0,"HELLO");
	LCD_String_xy(0, (uint8)12,"KIMO");
	LCD_Command(0xc0);
	
	for (loop = (uint8)0; loop < (uint8)8; loop++)
	{
		LCD_Char(Characters[loop]);
		LCD_Char(' ');
		
	}
}