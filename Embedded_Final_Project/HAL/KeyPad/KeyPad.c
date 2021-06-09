/*
 * KeyPad.c
 *
 * Created: 6/2/2021 1:05:05 PM
 *  Author: Mohamed Kamal
 */

#include <util/delay.h>
#include "DIO.h"
#include "KeyPad.h"
#include "KeyPad_Cfg.h"
#include "Display_MGR.h"
#include "Scheduler.h"

static void GetFirstInput();
static void GetSecondInput();

uint8 Characters[9] = {7, 8, 9, 4, 5, 6, 1, 2, 3};
uint8 Temperature = 0;
ParamCallback GlobalCallback;
uint8 GetSetTempRecFlag = 0;

void KeyPad_Init(void) {
    DIO_Init(2);
    DIO_Init(3);
    uint8 row;
    for (row = 0; row < 4; row++) {
        DIO_ChannelWrite(KeyPad_ConfigParam.RowsPortId, KeyPad_ConfigParam.RowsPinsChannels[row], 0xff);
    }
}

uint8 KeyPad_GetKey(void) {
    uint8 column;
    uint8 row;
    uint8 *rowPtr;
    uint8 key = NO_VALUE;
    for (column = 0; column < 3; column++) {
        DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId, KeyPad_ConfigParam.ColsPinsChannels[column], 0xff);
        for (row = 0; row < 4; row++) {
            DIO_ChannelRead(KeyPad_ConfigParam.RowsPortId, KeyPad_ConfigParam.RowsPinsChannels[row], rowPtr);
            if ((*rowPtr == 0x00)) {
                key = (row * 3 + column);
            }
        }
        DIO_ChannelDir(KeyPad_ConfigParam.ColsPortId, KeyPad_ConfigParam.ColsPinsChannels[column], 0x00);

    }
    return key;
}

void KeyPad_Enter(void) {
    uint8 key = KeyPad_GetKey();
    if (key == 0) {
        WriteSetTemp(Temperature);
        GlobalCallback(Temperature);
        Temperature = 0;
        if(GetSetTempRecFlag){
            Delay_ms(200, GetFirstInput);
        }
    } else {
        Delay_ms(200, KeyPad_Enter);
    }
}

void StopGetSetTemp(){
    GetSetTempRecFlag = 0;
    DeleteDelay_ms(GetFirstInput);
    DeleteDelay_ms(GetSecondInput);
    DeleteDelay_ms(KeyPad_Enter);
}

void StartGetSetTemp(){
    if(GetSetTempRecFlag == 0){
        GetSetTempRecFlag = 1;
        GetFirstInput();
    }
}
void GetSecondInput(void) {
    uint8 key = KeyPad_GetKey();
    if (key > 2 && key != 0xff) {
        Temperature = 10 * Temperature + Characters[key - 3];
        WriteSetTemp(Temperature);
        Delay_ms(200, KeyPad_Enter);
    } else if (key != 0) {
        Delay_ms(200, GetSecondInput);
    } else {
        WriteSetTemp(Temperature);
        Delay_ms(200, GetFirstInput);
    }
}

static void GetFirstInput() {
    uint8 key = KeyPad_GetKey();
    if (key != 0xff) {
        if (key > 2) {
            Temperature = Characters[key - 3];
            while (1) {
                key = KeyPad_GetKey();
                if (key == 0xff) {
                    WriteSetTemp(Temperature);
                    Delay_ms(200, GetSecondInput);
                    break;
                }
                _delay_us(100);
            }
        } else {
            if(GetSetTempRecFlag){
                Delay_ms(200, GetFirstInput);
            }
        }
    } else {
        if(GetSetTempRecFlag){
            Delay_ms(200, GetFirstInput);
        }
    }
}

void GetSetTempConfig(ParamCallback callback) {
    GlobalCallback = callback;
}

uint8 KeyPad_Get_Hash(void) {
    uint8 key;
    key = KeyPad_GetKey();
    uint8 result = 0;
    if (key == 2) {
        result = 1;
    }
    return result;
}