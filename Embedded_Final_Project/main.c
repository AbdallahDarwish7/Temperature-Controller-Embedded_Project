/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */
#include "main.h"
#include "Display_MGR.h"
#include "Mode_MGR.h"
#include "util/delay.h"
#include "Calibrator_Resistor.h"
#include "KeyPad.h"
#include "Temp_MGR.h"
#include "PWM.h"


int main(void) {
    config();
    _delay_ms(2000);
    uint8 oldCurrTemp = currentTemp;
    uint8 oldSetTemp = setTemp;
    MachineStateType machineState;
    while (1) {
        machineState = GetMachineState();
        if (machineState != ERROR){
            if (machineState != STANDBY){
                if ((currentTemp != oldCurrTemp) || (setTemp != oldSetTemp)){
                    if (((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5)) || ((setTemp > currentTemp) && ((setTemp - currentTemp) <= 5))){
                        SetMachineState(NORMAL);
                    } else{
                        SetMachineState(OPERATIONAL);
                    }
                    if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10)){
                        SetMachineState(ERROR);
                    }
                    write_CRT_Temp(currentTemp);
                    oldSetTemp = setTemp;
                    oldCurrTemp = currentTemp;
                }
            }
            if (KeyPad_Get_Hash()){
                machineState = GetMachineState();
                if (machineState == STANDBY){
                    SetMachineState(OPERATIONAL);
                } else if (machineState == NORMAL) {
                    SetMachineState(STANDBY);
                } else if (machineState == OPERATIONAL){
                    SetMachineState(STANDBY);
                }
            }
            _delay_ms(200);
        }
    }
}

void config(){
    Activate_LCD();
    display_Welcome_screen(1);
    TempMGR_Init();
    InitCalibrator();
    SystemPeriodicity_Init();
    KeyPad_Init();
}