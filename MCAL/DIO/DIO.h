#ifndef DIO_H_INCLUDED
#define DIO_H_INCLUDED

#define DIO_OK  ((unsigned char)0)
#define DIO_NOK ((unsigned char)1)

typedef unsigned char DIO_CheckType;
DIO_CheckType DIO_Init(unsigned char PortId);
DIO_CheckType DIO_ChannelDir(unsigned char PortId, unsigned char ChannelId, unsigned char Direction);
DIO_CheckType DIO_ChannelWrite(unsigned char PortId, unsigned char ChannelId, unsigned char Data);
DIO_CheckType DIO_ChannelRead(unsigned char PortId, unsigned char ChannelId, unsigned char *DataPtr);
DIO_CheckType DIO_PortDir(unsigned char PortId, unsigned char Direction);
DIO_CheckType DIO_PortWrite(unsigned char PortId, unsigned char Data);
DIO_CheckType DIO_PortRead(unsigned char PortId, unsigned char *DataPtr);

#endif // DIO_H_INCLUDED
