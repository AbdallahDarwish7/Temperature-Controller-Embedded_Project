//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//
#include "TC72.h"


void init(Mode operationMode){
    SPI_initMaster(MSB);
    SPI_sendByte(0x08);
    SPI_sendByte(operationMode);
}

uint8 ReadTemperature(void){
    int8 Msb;
    int8 Lsb;
    SPI_sendByte(0x02);
    Msb = SPI_recieveByte();
    Lsb = SPI_recieveByte();
}
