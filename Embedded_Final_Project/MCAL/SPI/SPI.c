/*
* Created by abdulla167
*/
#include "SPI.h"
#include <avr/io.h>
#include "Macros.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/******************** Initializing SPI as Master ***********************
 * Function:  SPI_InitMaster 
 * --------------------
 * used to initialize SPI in Master mode by:
 *		configuring SS, MOSI & SCK pins as OUTPUT pins and MISO pin as INPUT pin.
 *		configuring MSTR pin to 1 (Master mode).
 *		configuring Clock Frequency pins (SPR0, SPR1 & SPE). 
 *		configuring Data sending order (LSB || MSB). 
 *
 *  StartBit: first bit of data that will be sent.
 *
 *  ClkPhase: is used to shift the sampling phase on Leading(first) clock edge or Trailing(second) clock edge.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
void SPI_InitMaster(uint8 StartBit, uint8 ClkPhase) {
    /* SET SS PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, SS_PIN_NUM, (uint8) 0xff);
    /* SET MOSI PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, MOSI_PIN_NUM, (uint8) 0xff);
    /* SET MISO PIN AS INPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, MISO_PIN_NUM, (uint8) 0x00);
    /* SET SCK PIN AS OUTPUT PIN */
    DIO_ChannelDir(SPI_PORT_NUM, SCK_PIN_NUM, (uint8) 0xff);

    /*                ************** Justification *****************
     * Deviate from rule 11.3: may be unavoidable when addressing memory mapped registers or other hardware specific features
     */
    /* ENABLE MSTR BIT TO MAKE DEVICE THE MASTER */
    SET_BIT(SPCR, MSTR);
    /* SET CLOCK FREQUENCY = */
    CLEAR_BIT(SPCR, SPR0);
    CLEAR_BIT(SPCR, SPR1);
    /* SET SPE PIN TO ENABLE SPI */
    SET_BIT(SPCR, SPE);
    /* SEND DATA ORDER ACCORDING TO StartInput Parameter */
    if (StartBit == LSB) {
        SET_BIT(SPCR, DORD);
    } else {
        CLEAR_BIT (SPCR, DORD);
    }

    /* SAMPLING ON SECOND EDGE OF THE CLOCK */
    if (ClkPhase == LEADING_EDGE) {
        SET_BIT(SPCR, CPHA);
    } else {
        CLEAR_BIT (SPCR, CPHA);
    }
}


/******************** Sending byte by SPI ***********************
 * Function:  SPI_SendByte 
 * --------------------
 * used to send data via SPI by using SPDR(SPI Data Register):
 *
 *  data: data that will be sent by SPI.
 *
 */
uint8 SPI_SendByte(uint8 data) {
    SPDR = data;
    /*wait until SPI interrupt flag=1 (data0 is sent correctly)*/
    while (BIT_IS_CLEAR(SPSR, SPIF) == 1U) {}
    return SPDR;
}


/******************** Recieving byte by SPI ***********************
 * Function:  SPI_ReceiveByte
 * --------------------
 * used to send data via SPI by using SPDR(SPI Data Register):
 *
 *  returns: Data that is Received by SPI
 *           returns SPDR "Data Register" that contains received data
 */
uint8 SPI_ReceiveByte(void)
{
    while(BIT_IS_CLEAR(SPSR,SPIF) == 1U){} /*wait until SPI interrupt flag=1(data0 is receive correctly)*/
    return SPDR; /*return the received byte from SPI data0 register*/
}




