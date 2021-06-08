/*
 * KeyPad.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */ 



#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include "DIO.h"
#include "KeyPad.h"
#include "KeyPad_Cfg.h"
uint8 Characters[9] = { 7, 8, 9, 4, 5, 6, 1, 2, 3};
uint8 Temperature = 0;
void Initialize_KeyPad(void) {
	DIO_Init(2);
	DIO_Init(3);
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
	return key;
}
void enter(void){
	uint8 key = pressed_Key();
	if (key == 0)
	{
		write_Set_Temp(Temperature);
		Temperature = 0;
		Delay_ms(300, get_set_Temp);
	}else{
		Delay_ms(200, enter);
	}
}
void get_Second(void){
	uint8 key = pressed_Key();
	write_Set_Temp(Temperature);
	if(key >2 && key != 0xff ){
		Temperature = 10*Temperature +  Characters[key - 3];
		Delay_ms(200,enter);
	}else if (key !=0){
		Delay_ms(200,get_Second);
	}else{
		write_Set_Temp(Temperature);
		Delay_ms(200, get_set_Temp);
	}
}
void get_set_Temp(void){
	uint8 key = pressed_Key();
	if(key != 0xff){
		
		if(key>2) {
			Temperature = Characters[key - 3];
			uint8 second = 0;
			while(1){
				key = pressed_Key();
				if(key == 0xff){
					write_Set_Temp(Temperature);
					Delay_ms(300,get_Second);
					break;
					
				}
				_delay_us(100);
			}
		}else{
			Delay_ms(300, get_set_Temp);
		}
	}else{
		Delay_ms(300, get_set_Temp);
	}
}

uint8 get_Hash(void){
	uint8 key;
	key = pressed_Key();
	uint8 result = 0xff ;
	if(key == 2){
		result = '#';
	}
	return result;
}