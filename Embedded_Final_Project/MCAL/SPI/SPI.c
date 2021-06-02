#include "SPI.h"
#include <avr/io.h>
#include "DIO.h"
#include "Macros.h"

#define SPI_PORT ((unsigned char)1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void SPI_initMaster(void)
{
    /******** Configure SPI Master Pins *********
     * SS(PB4)   --> Output
     * MOSI(PB5) --> Output
     * MISO(PB6) --> Input
     * SCK(PB7) --> Output
     ********************************************/
    DIO_ChannelDir(1, 4, 0xff);
    DIO_ChannelDir(1, 5, 0xff);
    DIO_ChannelDir(1, 6, 0x00);
    DIO_ChannelDir(1, 7, 0xff);
    SPCR = (1<<SPE) | (1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_initSlave(void)
{
    /******** Configure SPI Slave Pins *********
     * SS(PB4)   --> Input
     * MOSI(PB5) --> Input
     * MISO(PB6) --> Output
     * SCK(PB7) --> Input
     ********************************************/
    DIO_ChannelDir(1, 4, 0x00);
    DIO_ChannelDir(1, 5, 0x00);
    DIO_ChannelDir(1, 6, 0xff);
    DIO_ChannelDir(1, 7, 0x00);
    SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
}

void SPI_sendByte(const unsigned char data)
{
    SPDR = data; //send data by SPI
    while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

unsigned char SPI_recieveByte(void)
{
    while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data is receive correctly)
    return SPDR; //return the received byte from SPI data register
}

void SPI_SendString(const unsigned char *Str)
{
    unsigned char i = 0;
    while(Str[i] != '\0')
    {
        SPI_sendByte(Str[i]);
        i++;
    }
}

void SPI_ReceiveString(char *Str)
{
    unsigned char i = 0;
    Str[i] = SPI_recieveByte();
    while(Str[i] != '#')
    {
        i++;
        Str[i] = SPI_recieveByte();
    }
    Str[i] = '\0';
}

