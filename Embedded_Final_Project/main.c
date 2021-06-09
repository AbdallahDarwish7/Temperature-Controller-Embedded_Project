/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */
#include "main.h"
#include "Display_MGR.h"
#include "Mode_MGR.h"
#include "Calibrator_Resistor.h"
#include "KeyPad.h"
#include "Temp_MGR.h"
#include "Scheduler.h"
#include "util/delay.h"

uint8 oldCurrTemp;
uint8 oldSetTemp;
MachineStateType machineState;


int main(void) {
    config();
    _delay_ms(2000);
    oldCurrTemp = currentTemp;
    oldSetTemp = setTemp;
//    Delay_ms(2000, AppFunc);
    get_set_Temp(UpdateInputTemp);
    while (1){
    };
}

void AppFunc() {
    machineState = GetMachineState();
    if (machineState != ERROR) {
        if (machineState != STANDBY) {
            if ((currentTemp != oldCurrTemp) || (setTemp != oldSetTemp)) {
                write_CRT_Temp(currentTemp);
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
        Delay_ms(200, &AppFunc);
    }
}

void config() {
    Activate_LCD();
    display_Welcome_screen(1);
    TempMGR_Init();
    InitCalibrator();
    SystemPeriodicity_Init();
    KeyPad_Init();
}