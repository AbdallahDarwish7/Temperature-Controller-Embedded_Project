#include "DIO.h"
#include "DIO_Cfg.h"

/*start address of each port*/
#define PORTA_BASE_ADDRESS ((uint8)0x3B)
#define PORTB_BASE_ADDRESS ((uint8)0x38)
#define PORTC_BASE_ADDRESS ((uint8)0x35)
#define PORTD_BASE_ADDRESS ((uint8)0x32)

/*Port subsystem registers offset*/
#define PORT_REG_OFFSET ((uint8)0)
#define DDR_REG_OFFSET ((uint8)1)
#define PIN_REG_OFFSET ((uint8)2)

#define NUM_OF_PORTS ((unsigned char)4)

/*Registers definitions*/
/*                ************** Justification *****************
 *                  Deviate from rule 19.7 (advisory)
 *                  This macro makes the code clearer and conciser
 */
#define PORT_REG(PORT_ID) (*((volatile uint8 *const)(PortBaseAddresses[PORT_ID] - PORT_REG_OFFSET)))
#define DDR_REG(PORT_ID) (*((volatile  uint8 *const)(PortBaseAddresses[PORT_ID] - DDR_REG_OFFSET)))
#define PIN_REG(PORT_ID) (*((volatile  uint8 *const)(PortBaseAddresses[PORT_ID] - PIN_REG_OFFSET)))

/*base address lookup table*/
const unsigned char PortBaseAddresses[NUM_OF_PORTS] =
        {
                PORTA_BASE_ADDRESS,
                PORTB_BASE_ADDRESS,
                PORTC_BASE_ADDRESS,
                PORTD_BASE_ADDRESS
        };

DIO_CheckType DIO_Init(uint8 PortId) {
    uint8 Loop;
    DIO_CheckType Result;
    /*verify Port Id*/
    if (PortId < NUM_OF_PORTS) {
        for (Loop =(uint8) 0; Loop < DIO_NUM_OF_PORT_CHANNELS; ++Loop) {
            /*init port direction for the masked pins*/
            DDR_REG(PortId) &= ~(DIO_ConfigParam[PortId][Loop].PortMask);
            DDR_REG(PortId) |= DIO_ConfigParam[PortId][Loop].PortMask & DIO_ConfigParam[PortId][Loop].PortDirection;
            /*init pull up resistor in case of input direction only*/
            PORT_REG(PortId) &= (~(DIO_ConfigParam[PortId][Loop].PortMask)) | (DIO_ConfigParam[PortId][Loop].PortDirection);
            PORT_REG(PortId) |= DIO_ConfigParam[PortId][Loop].PortMask &
                                ((~DIO_ConfigParam[PortId][Loop].PortDirection) & DIO_ConfigParam[PortId][Loop].IsPullupResistorUsed);
        }
        Result = DIO_OK;
    } else {
        /*invalid port*/
        Result = DIO_NOK;
    }
    return Result;
}

DIO_CheckType DIO_ChannelDir(uint8 PortId, uint8 ChannelId, uint8 Direction) {
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        if (ChannelId < DIO_NUM_OF_PORT_CHANNELS){
            DDR_REG(PortId) &= ~(1 << ChannelId);
            DDR_REG(PortId) |= ((1 << ChannelId) & Direction);
            Result = DIO_OK;
        } else{
            Result = DIO_NOK;
        }
    } else {
        Result = DIO_NOK;
    }
    return Result;
}


DIO_CheckType DIO_ChannelWrite(uint8 PortId, uint8 ChannelId, uint8 Data) {
    /*Add your code*/
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        if (ChannelId < DIO_NUM_OF_PORT_CHANNELS){
            PORT_REG(PortId) &= ~(1 << ChannelId);
            PORT_REG(PortId) |= (1 << ChannelId) & Data;
            Result = DIO_OK;
        } else{
            Result = DIO_NOK;
        }
    } else {
        Result = DIO_NOK;
    }
    return Result;
}


DIO_CheckType DIO_ChannelRead(uint8 PortId, uint8 ChannelId, uint8 *DataPtr) {
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        if (ChannelId < DIO_NUM_OF_PORT_CHANNELS){
            if ((1 << ChannelId) & PIN_REG(PortId)) {
                *DataPtr = (uint8)0xff;
            } else {
                *DataPtr = (uint8)0x00;
            }
            Result = DIO_OK;
        } else{
            Result = DIO_NOK;
        }
    } else {
        Result = DIO_NOK;
    }
    return Result;
}

DIO_CheckType DIO_PortDir(uint8 PortId, uint8 Direction) {
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        DDR_REG(PortId) = Direction;
        Result = DIO_OK;
    } else {
        Result = DIO_NOK;
    }
    return Result;
}

DIO_CheckType DIO_PortWrite(uint8 PortId, uint8 Data) {
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        PORT_REG(PortId) = Data;
        Result = DIO_OK;
    } else {
        Result = DIO_NOK;
    }
    return Result;
}

/******************* Reading Port Data ***********************
 * [Description] : Read the value of I/O port
 * [Parameters] :
 *
 */


DIO_CheckType DIO_PortRead(uint8 PortId, uint8 *DataPtr) {
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        *DataPtr = PIN_REG(PortId);
        Result = DIO_OK;
    } else {
        Result = DIO_NOK;
    }
    return Result;
}

