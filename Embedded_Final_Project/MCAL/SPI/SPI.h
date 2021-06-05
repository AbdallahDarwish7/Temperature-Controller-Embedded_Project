//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//

#ifndef FINAL_PROJECT_SPI_H
#define FINAL_PROJECT_SPI_H

#include "DIO.h"



#define SPI_PORT_NUM ((uint8)1)

/*******************************************************************************
 *                           DIO SPI Pins                                       *
 *******************************************************************************/
#define SS_PIN_NUM ((uint8)4)
#define MOSI_PIN_NUM ((uint8)5)
#define MISO_PIN_NUM ((uint8)6)
#define SCK_PIN_NUM ((uint8)7)

/*******************************************************************************
 *                      Sent Data Order Modes                                 *
 *******************************************************************************/
#define LSB ((uint8)1)
#define MSB ((uint8)0)

/*******************************************************************************
 *                      Clock Polarity Modes                                 *
 *******************************************************************************/
#define LEADING_EDGE ((uint8)0)
#define TRAILING_EDGE ((uint8)1)

/*******************************************************************************
 *                      Functions Declarations                                  *
 *******************************************************************************/

void SPI_InitMaster(uint8 StartBit, uint8 ClkPolarity);
void SPI_SendByte(uint8 data);
int8 SPI_RecieveByte(void);


#endif //FINAL_PROJECT_SPI_H
