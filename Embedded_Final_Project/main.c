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
#include "DIO.h"

uint8 DelayFlag = 0;
void callback(){
    DelayFlag = 1;
    Delay_ms(200, callback);
}

int main(void) {
    SystemConfig();
    Delay_ms(2000, callback);
    DIO_ChannelDir(0, 1, 0xff);
    uint8 oldCurrTemp;
    uint8 oldSetTemp;
    MachineStateType machineState;
    oldCurrTemp = currentTemp;
    oldSetTemp = setTemp;
    StartGetSetTemp();
    while (1){
        if(DelayFlag == 1){
            DelayFlag = 0;
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
        _delay_us(1);
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