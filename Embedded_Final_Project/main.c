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



int main(void) {
    config();
    _delay_ms(4000);
    SetMachineState(OPERATIONAL);
    while (1) {
//        if (machineState != ERROR){
//            if (((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5)) || ((setTemp > currentTemp) && ((setTemp - currentTemp) <= 5))){
//                SetMachineState(NORMAL);
//            } else{
//                SetMachineState(OPERATIONAL);
//            }
//            if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10)){
//                SetMachineState(ERROR);
//            }
//            if (KeyPad_Get_Hash()){
//                if (machineState == STANDBY){
//                    SetMachineState(OPERATIONAL);
//                } else if (machineState == OPERATIONAL || machineState == NORMAL){
//                    SetMachineState(STANDBY);
//                }
//            }
//        }
        write_CRT_Temp(currentTemp);
    }
}

void config(){
    Activate_LCD();
    display_Welcome_screen(1);
    InitCalibrator();
    SystemPeriodicity_Init();
    KeyPad_Init();
}

