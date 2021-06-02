#include "SPI.h"
#include <avr/io.h>
#include "DIO.h"
#include "../../Macros.h"

#define SPI_PORT_NUM ((unsigned char)1)
#define SS_PIN_NUM ((unsigned char)4)
#define MOSI_PIN_NUM ((unsigned char)5)
#define MISO_PIN_NUM ((unsigned char)6)
#define SCK_PIN_NUM ((unsigned char)7)
#define MSB ((unsigned char)1)
#define LSB ((unsigned char)0)


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/***********CONFIGURE DEVICE AS SPI MASTER************
 *
 * @param StartBit
 */
void SPI_initMaster(unsigned char StartBit)
{
    /* SET SS PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, SS_PIN_NUM, 0xff);
    /* SET MOSI PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, MOSI_PIN_NUM, 0xff);
    /* SET MISO PIN AS INPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, MISO_PIN_NUM, 0x00);
    /* SET SCK PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, SCK_PIN_NUM, 0xff);
    /* ENABLE MSTR BIT TO MAKE DEVICE THE MASTER */
    SET_BIT(SPCR, MSTR);
    /* SET CLOCK FREQUENCY = */
    CLEAR_BIT(SPIE, SPR0);
    CLEAR_BIT(SPIE, SPR1);
    /* SET SPE PIN TO ENABLE SPI */
    SET_BIT(SPCR, SPE);
    /* SET DATA ORDER ACCORDING TO StartInput Parameter */
    (StartBit == 1)? SET_BIT(SPCR , DORD) : CLEAR_BIT (SPCR , DORD;
}


/***********CONFIGURE DEVICE AS SPI SLAVE************
 *
 *
 */
void SPI_initSlave(void)
{
    /* SET SS PIN AS INPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, SS_PIN_NUM, 0x00);
    /* SET MOSI PIN AS INPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, MOSI_PIN_NUM, 0x00);
    /* SET MISO PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, MISO_PIN_NUM, 0xff);
    /* SET SCK PIN AS INPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, SCK_PIN_NUM, 0x00);
    /* SET SPE PIN TO ENABLE SPI */
    SET_BIT(SPCR, SPE);
}

/************* SEND BYTE OF DATA ********************
 *
 * @param data : THE DATA BYTE THAT WILL BE SENT TO THE SLAVE
 */
void SPI_sendByte(const unsigned char data)
{
    SPDR = data; //send data by SPI
    while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

/************* RECEIVE BYTE OF DATA ******************
 *
 * @return THE DATA WHICH HAVE BEEN READ FROM THE SLAVE
 */
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

