/*
 * LCD.h
 *
 * Created: 6/2/2021 3:13:29 PM
 *  Author: Mohamed Kamal
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "typedefs.h"
uint8 CheckBit(uint8 Data, uint8 bitNum);


void LCD_Write_Upper(uint8);

void LCD_Write_Lower(uint8);


void LCD_RS_Command(void);
	
void LCD_RS_Reg(void); 

void LCD_Read_Operation();

void LCD_Write_Operation();

void LCD_Enable(void); 

void LCD_Disable(void);

void LCD_WriteCommand(uint8 cmnd);

void LCD_WriteChar (uint8 char_data);  /* LCD data0 write function */

void LCD_Init (void);			/* LCD Initialize function */

void LCD_WriteString (uint8 *str);		/* Send string to LCD function */

void LCD_WriteStringAt_xy (uint8 row, uint8 pos, uint8 *str);  /* Send string to LCD with xy position */

void LCD_Clear();

void LCD_NewLine();

void LCD_Shift_R(void);

void LCD_Shift_L(void);

void LCD_Custom_Char(uint8 loc, uint8 *msg);

void test_LCD(void);

#endif /* LCD_H_ */