///*
// * Embedded_Final_Project.c
// *
// * Created: 6/2/2021 3:01:44 PM
// * Author : AbdallahDrwesh
// */
//
#include <avr/io.h>
#include <util/delay.h>
#include <TC72.h>


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


int main(void)
{
    DDRC=0xff;   //Configure PORTB as output
    DDRA=0xff;   //Configure PORTA as output
    float temp = 0.0;
    TC72_Init(CONTINUOUS_MODE);
    _delay_ms(150);
    while (1)
    {
        temp = TC72_ReadTemperature();
        display(temp);
    }
}
