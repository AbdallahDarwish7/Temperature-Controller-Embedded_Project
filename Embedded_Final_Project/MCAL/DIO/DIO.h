#ifndef DIO_H_INCLUDED
#define DIO_H_INCLUDED

#include "typedefs.h"

#define DIO_OK  ((unsigned char)0)
#define DIO_NOK ((unsigned char)1)

typedef unsigned char DIO_CheckType;
DIO_CheckType DIO_Init(uint8 PortId);
DIO_CheckType DIO_ChannelDir(uint8 PortId, uint8 ChannelId, uint8 Direction);
DIO_CheckType DIO_ChannelWrite(uint8 PortId, uint8 ChannelId, uint8 Data);
DIO_CheckType DIO_ChannelRead(uint8 PortId, uint8 ChannelId, uint8 *DataPtr);
DIO_CheckType DIO_PortDir(uint8 PortId, uint8 Direction);
DIO_CheckType DIO_PortWrite(uint8 PortId, uint8 Data);
DIO_CheckType DIO_PortRead(uint8 PortId, uint8 *DataPtr);

#endif /* DIO_H_INCLUDED */
