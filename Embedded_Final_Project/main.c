/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */
#include <util/delay.h>
#include "main.h"
#include "Display_MGR.h"
#include "Mode_MGR.h"
#include "Calibrator_Resistor.h"
#include "KeyPad.h"
#include "Temp_MGR.h"
#include "Scheduler.h"

uint8 DelayFlag = 0U;
void callback(){
    DelayFlag = 1U;
    Delay_ms(200U, callback);
}

int main(void) {
    SystemConfig();
    Delay_ms(2000U, callback);
    uint8 oldCurrTemp = currentTemp;
    uint8 oldSetTemp = setTemp;
    MachineStateType machineState;
    while (1){
        if(DelayFlag == 1U){
            DelayFlag = 0U;
            machineState = GetMachineState();
            if (machineState != ERROR) {
                if (machineState != STANDBY) {
                    if ((currentTemp != oldCurrTemp) || (setTemp != oldSetTemp)) {
                        write_CRT_Temp(currentTemp);
                        WriteSetTemp(setTemp);
                        oldSetTemp = setTemp;
                        oldCurrTemp = currentTemp;
                        if (((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5)) ||
                            ((setTemp > currentTemp) && ((setTemp - currentTemp) <= 5))) {
                            SetMachineState(NORMAL);
                        } else {
                            SetMachineState(OPERATIONAL);
                        }
                        if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10)) {
                            SetMachineState(ERROR);
                        }
                    }
                }
                if (KeyPad_Get_Hash()) {
                    machineState = GetMachineState();
                    if (machineState == STANDBY) {
                        SetMachineState(OPERATIONAL);
                    } else if ((machineState == NORMAL) || (machineState == OPERATIONAL)) {
                        SetMachineState(STANDBY);
                    }
                }
            }
        }
        _delay_us(1U);
    }
}

void SystemConfig() {
    Activate_LCD();
    display_Welcome_screen(1);
    TempMGR_Init();
    InitCalibrator();
    SystemPeriodicity_Config();
    KeyPad_Init();
    GetSetTempConfig(UpdateInputTemp);
}