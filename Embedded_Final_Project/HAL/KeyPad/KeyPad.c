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

void initialize_KeyPad(void) {
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

uint8 get_set_Temp(void){
	uint8 t = NO_VALUE;
	uint8 key = pressed_Key();
	if(key != 0xff){
		if(key>2) {
			t = Characters[key - 3];
			while(key != 0){
				key = pressed_Key();
				if(key == 0xff){
					while(key != 0){
						key = pressed_Key();
						if(key >2 && key != 0xff){
							t = 10*t +  Characters[key - 3];
							_delay_ms(100);
						}
					}
				}
			}
		}
	}
	return t;
}