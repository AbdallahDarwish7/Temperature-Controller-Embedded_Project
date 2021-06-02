//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//

#ifndef FINAL_PROJECT_SPI_H
#define FINAL_PROJECT_SPI_H

#include "typedefs.h"

#define SPI_PORT_NUM ((uint8)1)
#define SS_PIN_NUM ((uint8)4)
#define MOSI_PIN_NUM ((uint8)5)
#define MISO_PIN_NUM ((uint8)6)
#define SCK_PIN_NUM ((uint8)7)
#define MSB ((uint8)1)
#define LSB ((uint8)0)

void SPI_initMaster(uint8 StartBit);
void SPI_initSlave(void);
void SPI_sendByte(const uint8 data);
int8 SPI_recieveByte(void);
void SPI_sendString(const char *Str);
void SPI_receiveString(char *Str);

#endif //FINAL_PROJECT_SPI_H
