/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */


#include "Timer.h"
#include "DIO.h"

//#include "KeyPad.h"
//#include "Scheduler.h"
//#include <util/delay.h>
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
//    PeriodicDelay_ms(1000, ToggleBit0);
////    PeriodicDelay_ms(2000, ToggleBit1);
////    PeriodicDelay_ms(4000, ToggleBit2);
////    StartPeriodicDelay_ms(ToggleBit0);
////    _delay_ms(3000);
////    StopPeriodicDelay_ms(ToggleBit0);
//    while (1) {}
//}

#include "Temp_MGR.h"
#include "avr/io.h"
#include "avr/delay.h"

void display(char count);

int main(void) {
    Activate_TC72();
    DDRC=0xff;   //Configure PORTB as output
    DDRA=0xff;   //Configure PORTA as output
    // DDRC = DDRC & ~(1<<5) ; // Make pin 5 of port C as a input

    GICR=0xc0;   //Enable External Interrupts INT0 and INT1
    MCUCR=0x03;  // The rising edge of INT0 generates an interrupt request.
    DDRA &= ~(1 << PA0);
    PORTA |= (1 << PA0);
    while (1) {
        int8 temp = GetCurrentTemp();
        if (temp == NO_READ){
            display(99);
        } else{
            display(temp);
        }

    }
}

void display(char count){
    int digit1 = count%10 ;
    int digit1_bit = (digit1 >> 3) & 1U;
    if (digit1_bit == 1){
        digit1 = digit1 | (1<<4) ;
    }
    else{
        digit1 = digit1 & 0x247 ;
    }
    int digit2 = count/10 ;
    int digit2_bit = (digit2 >> 3) & 1U;
    if (digit2_bit == 1){
        digit2 = digit2 | (1<<4) ;
    }
    else{
        digit2 = digit2 & 0x247 ;
    }
    PORTA = PORTA | ( 1<<3) ; //PIN3 of port A is high
    PORTC = digit1;
    _delay_ms(5);
    PORTA = 0x00;
    PORTA = PORTA | ( 1<<2) ; //PIN2 of port A is high
    PORTC = digit2;
    _delay_ms(5);
    PORTA = 0x00;
}