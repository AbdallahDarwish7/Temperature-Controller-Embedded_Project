/*
 * KeyPad.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */


#include "DIO.h"
#include "KeyPad.h"
#include "KeyPad_Cfg.h"
#include "Display_MGR.h"
#include "Scheduler.h"
#include <util/delay.h>

static void GetFirstInput(void);
static void GetSecondInput(void);

static uint8 Characters[9] = {7, 8, 9, 4, 5, 6, 1, 2, 3};
uint8 Temperature = (uint8)0;
ParamCallback GlobalCallback;
uint8 GetSetTempRecFlag = (uint8)0;

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
    uint8 column;
    uint8 row1;
    uint8 *rowPtr;
    uint8 key = NO_VALUE;
    for (column = (uint8)0; column < (uint8) 3; column++) {
        DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId, KeyPad_ConfigParam.ColsPinsChannels[column], (uint8)0xff);
        for (row1 = (uint8)0; row1 < (uint8)4; row1++) {
            DIO_ChannelRead(KeyPad_ConfigParam.RowsPortId, KeyPad_ConfigParam.RowsPinsChannels[row1], rowPtr);
            if ((*rowPtr ==(uint8) 0x00)) {
                key = ((row1 * (uint8)3) + column);
            }
        }
        DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId, KeyPad_ConfigParam.ColsPinsChannels[column], (uint8)0x00);

    }
    return key;
}

void KeyPad_Enter(void) {
    uint8 key1 = KeyPad_GetKey();
    if (key1 == (uint8)0) {
        WriteSetTemp(Temperature);
        GlobalCallback(Temperature);
        Temperature =(uint8)0;
        if(GetSetTempRecFlag){
            Delay_ms((uint8)200, &GetFirstInput);
        }
    } else {
        Delay_ms((uint8)200, &KeyPad_Enter);
    }
}

void StopGetSetTemp(void){
    GetSetTempRecFlag =(uint8)0;
    DeleteDelay_ms(&GetFirstInput);
    DeleteDelay_ms(&GetSecondInput);
    DeleteDelay_ms(&KeyPad_Enter);
}

void StartGetSetTemp(void){
    if(GetSetTempRecFlag == (uint8)0){
        GetSetTempRecFlag = (uint8)1;
        GetFirstInput();
    }
}
static void GetSecondInput(void) {
    uint8 key2 = KeyPad_GetKey();
    if ((key2 > (uint8)2) && (key2 != (uint8)0xff)) {
        Temperature =((uint8) 10 * Temperature) + Characters[key2 - (uint8)3];
        WriteSetTemp(Temperature);
        Delay_ms((uint8)200, &KeyPad_Enter);
    } else if (key2 !=(uint8) 0) {
        Delay_ms((uint8)200, &GetSecondInput);
    } else {
        WriteSetTemp(Temperature);
        Delay_ms((uint8)200, &GetFirstInput);
    }
}

static void GetFirstInput(void) {

    uint8 key3 = KeyPad_GetKey();
    if (key3 != (uint8)0xff) {
        if (key3 > (uint8)2) {

            Temperature = Characters[key3 - (uint8)3];
            while (1) {
                key3 = KeyPad_GetKey();
                if (key3 == (uint8)0xff) {
                    WriteSetTemp(Temperature);
                    Delay_ms((uint8)200, &GetSecondInput);
                    break;
                }
                _delay_us((uint8)100);
            }
        } else {
            if(GetSetTempRecFlag){
                Delay_ms((uint8)200, &GetFirstInput);
            }
        }
    } else {
        if(GetSetTempRecFlag){
            Delay_ms((uint8)200, &GetFirstInput);
        }
    }
}

void GetSetTempConfig(ParamCallback callback) {
    GlobalCallback = callback;
}

uint8 KeyPad_Get_Hash(void) {
    uint8 key4= KeyPad_GetKey();
    uint8 result = 0;
    if (key4 == (uint8)2) {
        result = (uint8)1;
    }
    return result;
}
