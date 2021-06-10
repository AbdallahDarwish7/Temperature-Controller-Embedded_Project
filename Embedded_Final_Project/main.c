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
#include "Temp_MGR.h"
#include "Scheduler.h"
#include "typedefs.h"
uint8 DelayFlag = 0U;
int32 main(void) {
    SystemConfig();
    Delay_ms(6000U, &callback);
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
                        if ((uint8)((currentTemp > setTemp) && (uint8)((uint8)(currentTemp - setTemp) <= 5U)) ||
                            ((setTemp > currentTemp) && (uint8)((uint8)(setTemp - currentTemp) <= 5U))) {
                            SetMachineState(NORMAL);
                        } else {
                            SetMachineState(OPERATIONAL);
                        }
                        if ((currentTemp > setTemp) && ((uint8)(currentTemp - setTemp) > 10U)) {
                            SetMachineState(ERROR);
                        } else {

                        }
                    }
                } else {

                }
                if (IsReadyKeyPressed()) {
                    machineState = GetMachineState();
                    if (machineState == STANDBY) {
                        SetMachineState(OPERATIONAL);
                    } else if ((machineState == NORMAL) || (machineState == OPERATIONAL)) {
                        SetMachineState(STANDBY);
                    }else {

                    }
                }else{

                }
            } else{

            }
        }
        _delay_us(1U);
    }
}

void SystemConfig(void) {
    Activate_LCD();
    DisplayWelcomeScreen(3U);
    TempMGR_Init();
    InitCalibrator();
    SystemPeriodicity_Config();
}

void callback(void){
    DelayFlag = 1U;
    Delay_ms(200U, &callback);
}
