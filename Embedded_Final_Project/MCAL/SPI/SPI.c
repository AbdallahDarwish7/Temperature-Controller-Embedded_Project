//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//
#include "SPI.h"
#include <avr/io.h>
#include "Macros.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/********************** SPI_InitMaster **********************
 * [Description] :
 * @param StartBit
 * @param ClkPolarity
 */
void SPI_InitMaster(uint8 StartBit, uint8 ClkPolarity)
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
    CLEAR_BIT(SPCR, SPR0);
    CLEAR_BIT(SPCR, SPR1);
    /* SET SPE PIN TO ENABLE SPI */
    SET_BIT(SPCR, SPE);
    /* SEND DATA ORDER ACCORDING TO StartInput Parameter */
    (StartBit == LSB)? SET_BIT(SPCR , DORD) : CLEAR_BIT (SPCR , DORD);
    /* SAMPLING ON SECOND EDGE OF THE CLOCK */
    (ClkPolarity == LEADING_EDGE)? SET_BIT(SPCR , CPHA) : CLEAR_BIT (SPCR , CPHA);
}

/********************** SPI_SendByte **********************
 * [Description] :
 * @param data :
 */
void SPI_SendByte(uint8 data)
{
    SPDR = data; //send data0 by SPI
    while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data0 is sent correctly)
}

/**********************  SPI_RecieveByte **********************
 * [Description] :
 * @return THE DATA WHICH HAVE BEEN READ FROM THE SLAVE
 */
int8 SPI_RecieveByte(void)
{
    while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data0 is receive correctly)
    return SPDR; //return the received byte from SPI data0 register
}




