/*
* Created by abdulla167
*/

#include "TC72.h"

Mode TC72_mode = SHUTDOWN_MODE;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/



/******************** Initiate TC72 ***********************
 * Function:  TC72_Init 
 * --------------------
 * used to initialize TC72 device as master:
 *
 *  OperMode: Mode of TC72 Operation.
 * 
 */
void TC72_Init(Mode OperMode){
    /* INITIALIZE OUR DEVICE AS MASTER */
    SPI_InitMaster(MSB, LEADING_EDGE);
    /* SELECT MODE OF TC72 */
    TC72_Mode(OperMode);
}


/******************** Changing TC72 Mode ***********************
 * Function:  TC72_Mode 
 * --------------------
 * used to initialize TC72 device as slave:
 *
 *  OperMode: Mode of TC72 Operation.
 * 
 */
void TC72_Mode(Mode OperMode){
    /* ACTIVATE SLAVE TC72 */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, (uint8)0xff);
    /* SEND REGISTER CONTROL ADDRESS ON DATA LINE TO WRITE ON IT */
    SPI_SendByte(Control_Register_Address);
    /* SELECT OPERATION MODE FOR THE SENSOR ACCORDING TO OperationMode PARAMETER */
    TC72_mode = OperMode;
    SPI_SendByte(OperMode);
    /* DEACTIVATE THE TC72 AGAIN */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, (uint8)0x00);
}


/******************** Reading TC72 Temperature ***********************
 * Function:  TC72_ReadTemperature 
 * --------------------
 * used to initialize TC72 device as slave:
 * 
 */
uint8 TC72_ReadTemperature(void){
    uint8 dummy = 0x00;
    int8  MSBValue;
    /* ACTIVATE SLAVE TC72 */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, (uint8)0xff);
    /* SEND MSB DATA REGISTER ADDRESS TO GET THE DATA */
    SPI_SendByte(MSB_Register_Address);
    SPI_SendByte(dummy);
    /* DEACTIVATE SLAVE TC72 */
    DIO_ChannelWrite(SPI_PORT_NUM, SS_PIN_NUM, (uint8)0x00);
    /* READ SENSOR DATA FROM SPI DATA REGISTER */
    MSBValue = SPI_RecieveByte();
    return MSBValue;
}


/******************** Reading TC72 Mode ***********************
 * Function:  GetTC72Mode 
 * --------------------
 * used to initialize TC72 device as slave:
 *
 */
Mode GetTC72Mode(void){
    return TC72_mode;
}

