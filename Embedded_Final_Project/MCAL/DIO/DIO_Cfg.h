#ifndef DIO_CFG_H_INCLUDED
#define DIO_CFG_H_INCLUDED
#define DIO_NUM_OF_PORT_CHANNELS ((unsigned char)8)
#define DIO_NUM_OF_PORTS ((unsigned char)4)
#include "typedefs.h"

typedef struct
{
    uint8 PortMask;
    uint8 PortDirection;
    uint8 IsPullupResistorUsed;
}DIO_ConfigParamType;
extern const DIO_ConfigParamType DIO_ConfigParam[DIO_NUM_OF_PORTS][DIO_NUM_OF_PORT_CHANNELS];


#endif /*DIO_CFG_H_INCLUDED*/

