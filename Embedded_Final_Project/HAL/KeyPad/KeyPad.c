/*
 * KeyPad.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */


#include "DIO.h"
#include "KeyPad.h"
#include "KeyPad_Cfg.h"

static uint8 Characters[9] = {7, 8, 9, 4, 5, 6, 1, 2, 3};

void KeyPad_Init(void) {
    DIO_Init((uint8)2);
    DIO_Init((uint8)3);
    uint8 row;
    for (row = (uint8)0; row < (uint8)4; row++)
    {
        DIO_ChannelWrite(KeyPad_ConfigParam.RowsPortId, KeyPad_ConfigParam.RowsPinsChannels[row],(uint8) 0xff);
    }
}

uint8 KeyPad_GetKey(void)
{
    /* JUSTIFICATION: local variables for the same meaning */
    uint8 column;
    uint8 row;
    uint8 *rowPtr;
    uint8 key = NO_VALUE;
    for (column = (uint8)0; column < (uint8) 3; column++) {
        DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId, KeyPad_ConfigParam.ColsPinsChannels[column], (uint8)0xff);
        for (row = (uint8)0; row < (uint8)4; row++) {
            DIO_ChannelRead(KeyPad_ConfigParam.RowsPortId, KeyPad_ConfigParam.RowsPinsChannels[row], rowPtr);
            if ((*rowPtr ==(uint8) 0x00)) {
                key = ((row * (uint8)3) + column);
            }
        }
        DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId, KeyPad_ConfigParam.ColsPinsChannels[column], (uint8)0x00);

    }
    return key;
}

uint8 KeyPad_GetKeyValue(uint8 key){
    return Characters[key - (uint8)3];
}

uint8 KeyPad_Get_Hash(void) {
    /* JUSTIFICATION: local variables for the same meaning */
    uint8 key= KeyPad_GetKey();
    uint8 result = 0;
    if (key == (uint8)2) {
        result = (uint8)1;
    }
    return result;
}
