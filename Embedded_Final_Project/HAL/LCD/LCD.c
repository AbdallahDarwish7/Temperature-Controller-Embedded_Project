/*
 * CFile1.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */


#include "DIO.h"
#include "LCD.h"
#include "LCD_Cfg.h"
#include "Scheduler.h"
#include <util/delay.h>
uint8 data_global;
void LCD_Init_Delay(void);

uint8 CheckBit(uint8 Data, uint8 bitNum) {
    uint8 result;
    if (Data & (uint8)((uint8)1 << ((uint8)4 + bitNum))) {
        result = (uint8)0xff;
    } else {
        result = (uint8)0x00;
    }
    return result;
}

void LCD_Write_Upper(uint8 char_data) {
    char_data = (uint8)((char_data)& ((uint8)0xF0));
    uint8 loop;
    uint8 data;
    for (loop = (uint8) 0; loop < LCD_NUM_OF_DATA_PINS; loop++) {
        data = CheckBit(char_data, loop);
        DIO_ChannelWrite(LCD_ConfigParam.DataPortId, LCD_ConfigParam.DataPinsChannel[loop], data);
    }
}

void LCD_Write_Lower(uint8 char_data) {
    char_data = char_data << 4;
    /* JUSTIFICATION: local variables for the same meaning */
    uint8 loop;
    uint8 data;
    for (loop = (uint8) 0; loop < LCD_NUM_OF_DATA_PINS; loop++) {
        data = CheckBit(char_data, loop);
        DIO_ChannelWrite(LCD_ConfigParam.DataPortId, LCD_ConfigParam.DataPinsChannel[loop], data);
    }
}

void LCD_RS_Command(void) {
    DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RSPinChannel, (uint8)0x00);
}

void LCD_RS_Reg(void) {
    DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RSPinChannel, (uint8)0xff);
}

void LCD_Read_Operation(void) {
    DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RWPinChannel, (uint8)0xff);
}

void LCD_Write_Operation(void) {
    DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.RWPinChannel, (uint8)0x00);
}

void LCD_Enable(void) {
    DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.EnablePinChannel, (uint8)0xff);
}

void LCD_Disable(void) {
    DIO_ChannelWrite(LCD_ConfigParam.ControlPortId, LCD_ConfigParam.EnablePinChannel,(uint8)0x00);
}

void LCD_WriteCommand(uint8 cmnd) {
    data_global = cmnd;
    LCD_Write_Upper(cmnd);
    LCD_RS_Command();    /* RS=0 command reg. */
    LCD_Write_Operation();    /* RW=0 Write operation */
    LCD_Enable();    /* Enable pulse */
    _delay_us(1);
    LCD_Disable();
    _delay_us(100);
    /*Delay_ms(1, LCD_Write_Lower);*/
    LCD_Write_Lower(cmnd);
    LCD_RS_Command();    /* RS=0 command reg. */
    LCD_Write_Operation();    /* RW=0 Write operation */
    LCD_Enable();    /* Enable pulse */
    _delay_us(1);
    LCD_Disable();
    _delay_us(2);
}

void LCD_WriteChar(uint8 char_data)  /* LCD data0 write function */
{
    data_global = char_data;
    LCD_Write_Upper(char_data);
    LCD_RS_Reg();    /* RS=0 command reg. */
    LCD_Write_Operation();    /* RW=0 Write operation */
    LCD_Enable();    /* Enable pulse */
    _delay_us((float32)1);
    LCD_Disable();
    _delay_us((float32)100);            /* Data write DelayFlag */
    LCD_Write_Lower(char_data);
    LCD_RS_Reg();    /* RS=0 command reg. */
    LCD_Write_Operation();    /* RW=0 Write operation */
    LCD_Enable();    /* Enable pulse */
    _delay_us((float32)1);
    LCD_Disable();
    _delay_us((float32)2);
}

void LCD_Init_Delay(void) {
    LCD_WriteCommand((uint8)0X02);
    LCD_WriteCommand((uint8)0x28);        /* Initialization of 16X2 LCD in 8bit mode */
    LCD_WriteCommand((uint8)0x0C);        /* Display ON Cursor OFF */
    LCD_WriteCommand((uint8)0x06);        /* Auto Increment cursor */
    LCD_WriteCommand((uint8)0x01);        /* clear display */
    _delay_us((float32)2);
}

void LCD_Init(void)            /* LCD Initialize function */
{
    DIO_Init((uint8)2);
    DIO_Init((uint8)3);
    Delay_ms((uint8)20, &LCD_Init_Delay);        /* LCD Power ON DelayFlag always >15ms */
    LCD_WriteCommand((uint8)0X02);
    LCD_WriteCommand((uint8)0x28);        /* Initialization of 16X2 LCD in 8bit mode */
    LCD_WriteCommand((uint8)0x0C);        /* Display ON Cursor OFF */
    LCD_WriteCommand((uint8)0x06);        /* Auto Increment cursor */
    LCD_WriteCommand((uint8)0x01);        /* clear display */
    _delay_us((float32)2);
}


void LCD_WriteString(const uint8 str[])        /* Send string to LCD function */
{
    /* JUSTIFICATION: local variable for the same meaning */
    uint16 loop;
    for (loop = (uint16)0; str[loop] != (uint8)'\0'; loop++)        /* Send each char of string till the NULL */
    {
        LCD_WriteChar((uint8) str[loop]);
    }
}

void LCD_WriteStringAt_xy(uint8 row, uint8 pos, const uint8 str[])  /* Send string to LCD with xy position */
{
    if ((row == (uint8)0) && (pos < (uint8)16))
    {
        LCD_WriteCommand((pos & (uint8)0x0F) | (uint8)0x80);
    }    /* Command of first row and required position<16 */
    else if ((row == (uint8)1) && (pos < (uint8)16))
    {
        LCD_WriteCommand((pos & (uint8)0x0F) | (uint8)0xC0);    /* Command of first row and required position<16 */
    }
    else{}

    LCD_WriteString(str);        /* Call LCD string function */
}

void LCD_Clear(void) {
    LCD_WriteCommand((uint8)0x01);        /* clear display */
}

void LCD_NewLine(void) {
    LCD_WriteCommand((uint8)0xc0);        /* clear display */
}

void LCD_Shift_R(void) {
    LCD_WriteCommand((uint8)0x1c);
}

void LCD_Shift_L(void) {
    LCD_WriteCommand((uint8)0x18);
}

void LCD_Custom_Char(uint8 loc, const uint8 msg[]) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 loop;
    if (loc < (uint8)8) {
        LCD_WriteCommand((uint8)0x40 + (loc * (uint8)8));    /* Command 0x40 and onwards forces the device to point CGRAM address */
        for (loop = (uint8)0; loop < (uint8)8; loop++)    /* Write 8 byte for generation of 1 character */
        {
            LCD_WriteChar(msg[loop]);
        }
    }
}

/*void test_LCD(void) {
    uint8 loop4;

    uint8 Characters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    DIO_Init((uint8)2);
    DIO_Init((uint8)3);
    LCD_Init();
    LCD_WriteCommand((uint8)0x80);
    LCD_WriteString(" ");
    LCD_WriteStringAt_xy(0, (uint8) 0, "HELLO");
    LCD_WriteStringAt_xy(0, (uint8) 12, "Kamal");
    LCD_WriteCommand(0xc0);

    for (loop4 = (uint8) 0; loop4 < (uint8) 8; loop4++) {
        LCD_WriteChar(Characters[loop4]);
        LCD_WriteChar(' ');

    }
}
*/
