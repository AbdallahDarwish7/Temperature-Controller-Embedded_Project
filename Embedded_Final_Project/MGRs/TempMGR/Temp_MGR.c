/*
* Created by abdulla167
*/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "KeyPad.h"
#include "typedefs.h"
#include "TC72.h"
#include "Temp_MGR.h"
#include "Scheduler.h"
#include "Display_MGR.h"
#include <util/delay.h>

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

uint8 currentTemp = 25;
uint8 setTemp = 25;
uint8 Temperature = (uint8)0;
ParamCallback GlobalCallback;
uint8 GetSetTempRecFlag = (uint8)0;

static void GetFirstInput(void);
static void GetSecondInput(void);
static void WaitEnterKey(void);
/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/


/******************** Updating Temperature values ***********************
 * Function:  UpdateCurrentTemp 
 * --------------------
 * used to update the value of current temperature from TC72 sensor according to Sensor mode:
 *		SHUTDOWN_MODE : No temperature to be read
 *		At any other mode: read temperature from sensor and update CurrentTemp "Global Variable"
 *
 */
void UpdateCurrentTemp(void){
    Mode TC72Mode = GetTC72Mode();
    if (TC72Mode == SHUTDOWN_MODE){
        currentTemp = NO_READ;
    } else{
        currentTemp = (uint8)TC72_ReadTemperature();
    }
}

/******************** Updating Temperature values ***********************
 * Function:  UpdateInputTemp 
 * --------------------
 * used to update the value of Set temperature from Keypad:
 *
 * InputTemp: The value of temperature written on the keypad
 *
 */
void UpdateInputTemp(uint8 InputTemp){
    setTemp = InputTemp;
}


/******************** Temperature Manager Initiation ***********************
 * Function:  TempMGR_Init 
 * --------------------
 * used to initiate TC72 sensor after power on and no temperature reading "SHUTDOWN_MODE".
 *
 */
void TempMGR_Init(void){
    TC72_Init(SHUTDOWN_MODE);
    KeyPad_Init();
    GetSetTempConfig(UpdateInputTemp);
}


/******************** Temperature Manager Deactivate TC72 ***********************
 * Function:  Deactivate_TC72 
 * --------------------
 * used to deactivate TC72 sensor by applying "SHUTDOWN_MODE".
 *
 */
void Deactivate_TC72(void){
    if (GetTC72Mode() != SHUTDOWN_MODE){
        TC72_Mode(SHUTDOWN_MODE);
    }
}


/******************** Temperature Manager Deactivate TC72 ***********************
 * Function:  Deactivate_TC72 
 * --------------------
 * used to Config the TC72 sensor to the continuous mode.
 *
 */
void Activate_TC72(void){
    if (GetTC72Mode() != CONTINUOUS_MODE){
        TC72_Mode(CONTINUOUS_MODE);
    }
}

void GetSetTempConfig(ParamCallback callback) {
    GlobalCallback = callback;
}

void StopGetSetTemp(void){
    GetSetTempRecFlag =(uint8)0;
    DeleteDelay_ms(&GetFirstInput);
    DeleteDelay_ms(&GetSecondInput);
    DeleteDelay_ms(&WaitEnterKey);
}

void StartGetSetTemp(void){
    if(GetSetTempRecFlag == (uint8)0){
        GetSetTempRecFlag = (uint8)1;
        GetFirstInput();
    }
}
static void WaitEnterKey(void) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 key = KeyPad_GetKey();
    if (key == (uint8)0) {
        WriteSetTemp(Temperature);
        GlobalCallback(Temperature);
        Temperature =(uint8)0;
        if(GetSetTempRecFlag){
            Delay_ms((uint32)200, &GetFirstInput);
        }
    } else {
        Delay_ms((uint32)200, &WaitEnterKey);
    }
}

static void GetSecondInput(void) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 key = KeyPad_GetKey();
    if ((key > (uint8)2) && (key != (uint8)0xff)) {
        Temperature =((uint8) 10 * Temperature) + KeyPad_GetKeyValue(key);
        WriteSetTemp(Temperature);
        Delay_ms((uint32)200, &WaitEnterKey);
    } else if (key != (uint8) 0) {
        Delay_ms((uint32)200, &GetSecondInput);
    } else {
        WriteSetTemp(Temperature);
        Delay_ms((uint32)200, &GetFirstInput);
    }
}

static void GetFirstInput(void) {
    /* JUSTIFICATION: local variable for the same meaning */
    uint8 key = KeyPad_GetKey();
    if (key != (uint8)0xff) {
        if (key > (uint8)2) {
            Temperature = KeyPad_GetKeyValue(key);
            while (1) {
                key = KeyPad_GetKey();
                if (key == (uint8)0xff) {
                    WriteSetTemp(Temperature);
                    Delay_ms((uint32)200, &GetSecondInput);
                    break;
                }
                _delay_us((float32)100);
            }
        } else {
            if(GetSetTempRecFlag){
                Delay_ms((uint32)200, &GetFirstInput);
            }
        }
    } else {
        if(GetSetTempRecFlag){
            Delay_ms((uint32)200, &GetFirstInput);
        }
    }
}