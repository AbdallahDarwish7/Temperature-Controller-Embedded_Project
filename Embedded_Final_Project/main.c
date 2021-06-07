/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */

//#include "typedefs.h"
//#include "DIO.h"
//#include "Scheduler.h"
//
//uint8 data0 = 0xff;
//uint8 data1 = 0xff;
//uint8 data2 = 0xff;
//void ToggleBit0(void) {
//    DIO_ChannelWrite(0, 0, data0);
//    data0 ^= 0xff;
//}
//
//void ToggleBit1(void) {
//    DIO_ChannelWrite(0, 1, data1);
//    data1 ^= 0xff;
//}
//void ToggleBit2(void) {
//    DIO_ChannelWrite(0, 2, data2);
//    data2 ^= 0xff;
//}
//int main(void) {
//
//    /* test lcd keypad */
////    test_KeyPad_Lcd();
////    /* test pwd */
////    float Percentage = 20;
////    DIO_ChannelDir(1, 3, 0xff);
////    Timer_Init(0, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
////    PWM_SetDutyCycle(0, Percentage, TIMER_PWD_PHASE_CORRECT_MODE, TIMER_NON_INVERTED_COM);
////    Timer_Start(0, TIMER0_PRESCALER_8);
//    DIO_ChannelDir(0, 0, 0xff);
//    DIO_ChannelDir(0, 1, 0xff);
//    DIO_ChannelDir(0, 2, 0xff);
//    PeriodicDelay_ms(100, ToggleBit0);
//    PeriodicDelay_ms(200, ToggleBit1);
//    PeriodicDelay_ms(400, ToggleBit2);
//    StartPeriodicDelay_ms(ToggleBit0);
//    StartPeriodicDelay_ms(ToggleBit1);
//    StartPeriodicDelay_ms(ToggleBit2);
////    _delay_ms(8000);
////    StopPeriodicDelay_ms(ToggleBit2);
////    StopPeriodicDelay_ms(ToggleBit1);
//    while (1) {}
//}

#include "LCD_Manager.h"
#include "LCD.h"
#include "ADC.h"
#include <avr/delay.h>
#include <stdlib.h>


int main() {
    Init_ADC(0);
    LCD_Init();
    _delay_ms(100);
    LCD_Command(0x0C);
    _delay_ms(100);

    LCD_Command(0x01);

    LCD_Char(' ');
    _delay_ms(1);
    LCD_Char('K');
    _delay_ms(1);
    LCD_Char('P');
    _delay_ms(1);
    LCD_Char('a');
    _delay_ms(1);
    LCD_Char('d');
    _delay_ms(1);
    LCD_Char('=');
    _delay_ms(1);

    LCD_Command(0xC0);
    _delay_ms(1);
    LCD_Command(0x0C);
    _delay_ms(1);

    LCD_Char('F');
    _delay_ms(1);
    LCD_Char('i');
    _delay_ms(1);
    LCD_Char('n');
    _delay_ms(1);
    LCD_Char('a');
    _delay_ms(1);
    LCD_Char('l');
    _delay_ms(1);
    LCD_Char(' ');
    _delay_ms(1);
    LCD_Char('=');
    _delay_ms(1);
    LCD_Char(' ');
    char ch[4] = {' '};
    uint16_t Reading = 89;
    while (1) {
        Reading = ADC_Read(0);        /*ADC Reading pin*/
        for (int j = 0; j < 4; j++) {
            ch[j] = ' ';
        }
        LCD_String_xy(1, 7, " ");
        itoa(Reading, ch, 10);
        for (int j = 0; j < 4; j++) {
            if (ch[j] < '0' || ch[j] > '9') {
                LCD_Char(' ');
            } else {
                LCD_Char(ch[j]);
            }
        }
        _delay_ms(200);
    }
}



