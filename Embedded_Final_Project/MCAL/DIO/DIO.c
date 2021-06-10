#include "DIO.h"
#include "DIO_Cfg.h"

/*******************************************************************************
 *                         Start address of each port                          *
 *******************************************************************************/
#define PORTA_BASE_ADDRESS ((uint8)0x3B)
#define PORTB_BASE_ADDRESS ((uint8)0x38)
#define PORTC_BASE_ADDRESS ((uint8)0x35)
#define PORTD_BASE_ADDRESS ((uint8)0x32)

/*******************************************************************************
 *                        Port subsystem registers offset                      *
 *******************************************************************************/
#define PORT_REG_OFFSET ((uint8)0)
#define DDR_REG_OFFSET ((uint8)1)
#define PIN_REG_OFFSET ((uint8)2)

#define NUM_OF_PORTS ((unsigned char)4)


/*******************************************************************************
 *                                Justification                                *
 *---------------------------------------------------------------------------             
 *                  Deviate from rule 19.7 (advisory)
 *                  This macro makes the code clearer and conciser
 *---------------------------------------------------------------------------
 *                  Deviate from rule 11.3:
 *                  may be unavoidable when addressing memory mapped registers or other hardware specific features
 *---------------------------------------------------------------------------
 *                  Deviate from rule 5.7:
 *                  local variable for the same meaning
 *---------------------------------------------------------------------------
 *                  :
 */
/*******************************************************************************
 *                        Registers definitions                                *
 *******************************************************************************/
#define PORT_REG(PORT_ID) (*((volatile uint8 *const)(PortBaseAddresses[(PORT_ID)] - PORT_REG_OFFSET)))
#define DDR_REG(PORT_ID) (*((volatile  uint8 *const)(PortBaseAddresses[(PORT_ID)] - DDR_REG_OFFSET)))
#define PIN_REG(PORT_ID) (*((volatile  uint8 *const)(PortBaseAddresses[(PORT_ID)] - PIN_REG_OFFSET)))


/*******************************************************************************
 *                        Base address lookup table                                *
 *******************************************************************************/
const unsigned char PortBaseAddresses[NUM_OF_PORTS] =
        {
                PORTA_BASE_ADDRESS,
                PORTB_BASE_ADDRESS,
                PORTC_BASE_ADDRESS,
                PORTD_BASE_ADDRESS
        };


/******************** Initializing Digital I/O ***********************
 * Function:  DIO_Init 
 * --------------------
 * used to activate the the Selected port :
 *
 *  PortId: Port Number that selected to be initialized.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
DIO_CheckType DIO_Init(uint8 PortId) {
    uint8 Loop;
    DIO_CheckType Result;
    /*verify Port Id*/
    if (PortId < NUM_OF_PORTS) {
        for (Loop =(uint8) 0; Loop < DIO_NUM_OF_PORT_CHANNELS; ++Loop) {
            /* Init port direction for the masked pins*/
            DDR_REG(PortId) = DDR_REG(PortId) & ((uint8)~(DIO_ConfigParam[PortId][Loop].PortMask));
            DDR_REG(PortId) = DDR_REG(PortId) | (DIO_ConfigParam[PortId][Loop].PortMask & DIO_ConfigParam[PortId][Loop].PortDirection);
            /* Init pull up resistor in case of input direction only*/
            PORT_REG(PortId) = PORT_REG(PortId) & ((uint8)(~(DIO_ConfigParam[PortId][Loop].PortMask)) | (DIO_ConfigParam[PortId][Loop].PortDirection));
            PORT_REG(PortId) =PORT_REG(PortId) | (DIO_ConfigParam[PortId][Loop].PortMask &
                                ((uint8)(~DIO_ConfigParam[PortId][Loop].PortDirection) & DIO_ConfigParam[PortId][Loop].IsPullupResistorUsed));
        }
        Result = DIO_OK;
    } else {
        /*invalid port*/
        Result = DIO_NOK;
    }
    return Result;
}


/******************** Indicates Channel Direction ***********************
 * Function:  DIO_ChannelDir 
 * --------------------
 * used to determine the direction of the Channel within the port is "input" or "output":
 *
 *  PortId: Port Number that contain the channel that will updated.
 *
 *  Direction: indicates whether the channel is input or output.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
DIO_CheckType DIO_ChannelDir(uint8 PortId, uint8 ChannelId, uint8 Direction) {
    /* JUSTIFICATION: local variable for the same meaning */
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        if (ChannelId < DIO_NUM_OF_PORT_CHANNELS){
            DDR_REG(PortId) = DDR_REG(PortId) & ((uint8)(~((uint8)((uint8)1 << ChannelId))));
            DDR_REG(PortId) = DDR_REG(PortId) | ((uint8)((uint8)((uint8)1 << ChannelId) & Direction));
            Result = DIO_OK;
        } else{
            Result = DIO_NOK;
        }
    } else {
        Result = DIO_NOK;
    }
    return Result;
}


/******************** Writing Channel Data ***********************
 * Function:  DIO_ChannelWrite 
 * --------------------
 * used to read the value Channel of I/O port:
 *
 *  PortId: Port Number that selected to write a data on it.
 *
 *  ChannelId: Channel Number within PortId that store the data.
 *
 *  Data: data that written on the ChannelId selected.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
DIO_CheckType DIO_ChannelWrite(uint8 PortId, uint8 ChannelId, uint8 Data) {
    /*Add your code*/
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        if (ChannelId < DIO_NUM_OF_PORT_CHANNELS){
            PORT_REG(PortId) = PORT_REG(PortId) & ((uint8)(~((uint8)(1U << ChannelId))));
            PORT_REG(PortId) = PORT_REG(PortId) | (((uint8)(1U << ChannelId) & Data));
            Result = DIO_OK;
        } else{
            Result = DIO_NOK;
        }
    } else {
        Result = DIO_NOK;
    }
    return Result;
}


/******************** Reading Channel Data ***********************
 * Function:  DIO_ChannelRead 
 * --------------------
 * used to read the value Channel of I/O port:
 *
 *  PortId: Port Number that selected to read a data from it.
 *
 *  ChannelId: Channel Number within PortId that contains data.
 *
 *  DataPtr: pointer that indicate the address of the stored data read from the channel.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
DIO_CheckType DIO_ChannelRead(uint8 PortId, uint8 ChannelId, uint8 *DataPtr) {
    /* JUSTIFICATION: local variable for the same meaning */
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        if (ChannelId < DIO_NUM_OF_PORT_CHANNELS){
            if (((uint8)((uint8)1 << ChannelId) & PIN_REG(PortId))) {
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


/******************** Indicates Port Direction ***********************
 * Function:  DIO_PortDir 
 * --------------------
 * used to determine the direction of the port "input" or "output":
 *
 *  PortId: Port Number that selected to update it's direction.
 *
 *  Direction: indicates whether the port is input or output.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
DIO_CheckType DIO_PortDir(uint8 PortId, uint8 Direction) {
    /* JUSTIFICATION: local variable for the same meaning */
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        DDR_REG(PortId) = Direction;
        Result = DIO_OK;
    } else {
        Result = DIO_NOK;
    }
    return Result;
}


/******************** Writing Port Data ***********************
 * Function:  DIO_PortWrite 
 * --------------------
 * used to write a particular data on I/O port:
 *
 *  PortId: Port Number that selected to write a data on it.
 *
 *  Data: data that written on the PortId selected.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
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


/******************** Reading Port Data ***********************
 * Function:  DIO_PortWrite 
 * --------------------
 * used to read the value of I/O port:
 *
 *  PortId: Port Number that selected to read a data from it.
 *
 *  DataPtr: pointer that indicate the address of the stored data read from the port.
 *
 *  returns: Type that indicates the function is executed successfully 
 *           or there's error occurred during execution
 *           returns DIO_OK on Success 
 *           returns DIO_NOK on Error 
 */
DIO_CheckType DIO_PortRead(uint8 PortId, uint8 *DataPtr) {
    /* JUSTIFICATION: local variable for the same meaning */
    DIO_CheckType Result;
    if (PortId < DIO_NUM_OF_PORTS) {
        *DataPtr = (uint8)PIN_REG(PortId);
        Result = DIO_OK;
    } else {
        Result = DIO_NOK;
    }
    return Result;
}

