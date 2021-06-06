//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//

#include <util/delay.h>
#include "TC72.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/



/********************** TC72_Init **********************
 * [Description] :
 * @param OperationMode
 */
void TC72_Init(Mode OperationMode){
    /* INITIALIZE OUR DEVICE AS MASTER */
    SPI_InitMaster(MSB, LEADING_EDGE);
    /* ACTIVATE SLAVE TC72 */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, 0xff);
    /* SEND REGISTER CONTROL ADDRESS ON DATA LINE TO WRITE ON IT */
    SPI_SendByte(Control_Register_Address);
    /* SELECT OPERATION MODE FOR THE SENSOR ACCORDING TO OperationMode PARAMETER */
    SPI_SendByte(OperationMode);
    /* DEACTIVATE THE TC72 AGAIN */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, 0x00);
}

/********************** TC72_ReadTemperature **********************
 * [Description] :
 * @return
 */
float TC72_ReadTemperature(void){
    uint8 dummy = 0x00;
    uint8  MSBValue;
    /* ACTIVATE SLAVE TC72 */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, 0xff);
    /* SEND MSB DATA REGISTER ADDRESS TO GET THE DATA */
    SPI_SendByte(MSB_Register_Address);
    SPI_SendByte(dummy);
    /* DEACTIVATE SLAVE TC72 */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, 0x00);
    _delay_ms(1);
    /* READ SENSOR DATA FROM SPI DATA REGISTER */
    MSBValue = SPI_RecieveByte();
    return MSBValue;
}
