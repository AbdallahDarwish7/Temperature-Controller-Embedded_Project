/*
 * KeyPad.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */ 

 #define KEYPAD B  //KEYPAD IS ATTACHED ON PORTA
 
  //Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR   DDR(KEYPAD)
#define KEYPAD_PIN   PIN(KEYPAD)

#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include "DIO.h"
#include "KeyPad.h"
#include "KeyPad_Cfg.h"
#include "LCD.h"

void initialize_KeyPad(void) {
	uint8 r;
	for(r=0;r<4;r++)
	{
		DIO_ChannelWrite(KeyPad_ConfigParam.RowsPortId,KeyPad_ConfigParam.RowsPinsChannels[r], 0xff);
	}
}

uint8 pressed_Key(void){

	uint8 c;
	uint8 r;
	uint8* row; 
	
	uint8 key = 0xff;
	for(c=0;c<3;c++)
	{
		DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId,KeyPad_ConfigParam.ColsPinsChannels[c], 0xff);
		for(r=0;r<4;r++)
		{
			DIO_ChannelRead(KeyPad_ConfigParam.RowsPortId, KeyPad_ConfigParam.RowsPinsChannels[r], row);
			if((*row == 0x00))
			{
				key =  (r*3 +c);
			}
		}
		DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId,KeyPad_ConfigParam.ColsPinsChannels[c], 0x00);
		
	}
	return key;//Indicate No key pressed*
}


void test_KeyPad_Lcd(void) {
	unsigned char loop;
	uint8* Characters[12] = {"*", "0", "3", "7", "8", "9", "4", "5", "6", "3", "2", "1"};

	DIO_Init(2);
	DIO_Init(3);
	DIO_Init(1);
	initialize_KeyPad();
	LCD_Init();
	LCD_Command(0x80);
	LCD_String(" ");
	LCD_String("HELLO: ");
	LCD_String_xy(0, (uint8)10,"KIMO");
	LCD_Command(0xc0);
	uint8 key;
	while(1)
	{
		key = pressed_Key();
		if(key != 0xff){
			LCD_String_xy(1, 0, Characters[key]);
		}
	}
}