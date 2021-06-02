//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//

#ifndef FINAL_PROJECT_SPI_H
#define FINAL_PROJECT_SPI_H
typedef unsigned char uint8;
void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const uint8 data);
uint8 SPI_recieveByte(void);
void SPI_sendString(const uint8 *Str);
void SPI_receiveString(char *Str);

#endif //FINAL_PROJECT_SPI_H
