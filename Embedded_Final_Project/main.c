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


//uint8 data0 = 0xff;
//uint8 data1 = 0xff;
//uint8 data2 = 0xff;
//void ToggleBit0(void) {
//    DIO_ChannelWrite(0, 0, data0);
//    data0 ^= 0xff;
//}
//
//void ToggleBit1(void) {
//    DIO_ChannelWrite(0, 1, data1);
//    data1 ^= 0xff;
//}
//void ToggleBit2(void) {
//    DIO_ChannelWrite(0, 2, data2);
//    data2 ^= 0xff;
//}

void callback(){
    SetMachineState(OPERATIONAL);
    write_CRT_Temp(32);
}
int main(void) {
//    DIO_ChannelDir(0, 0, 0xff);
//    DIO_ChannelDir(0, 1, 0xff);
//    DIO_ChannelDir(0, 2, 0xff);
//    PeriodicDelay_ms(100, ToggleBit0);
//    PeriodicDelay_ms(200, ToggleBit1);
//    PeriodicDelay_ms(400, ToggleBit2);
//    StartPeriodicDelay_ms(ToggleBit0);
//    StartPeriodicDelay_ms(ToggleBit1);
//    StartPeriodicDelay_ms(ToggleBit2);
//    _delay_ms(8000);
//    StopPeriodicDelay_ms(ToggleBit2);
//    StopPeriodicDelay_ms(ToggleBit1);
    config();
    _delay_ms(1500);
    uint8 oldCurrTemp = currentTemp;
    uint8 oldSetTemp = setTemp;
    while (1) {
        if (machineState != ERROR){
            if (machineState != STANDBY){
                if ((currentTemp != oldCurrTemp) || (setTemp != oldSetTemp)){
                    if (((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5)) || ((setTemp > currentTemp) && ((setTemp - currentTemp) <= 5))){
                        write_State(NORMAL);
                        SetMachineState(NORMAL);
                    } else{
                        write_State(OPERATIONAL);
                        SetMachineState(OPERATIONAL);
                    }
                    if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10)){
                        write_State(ERROR);
                        SetMachineState(ERROR);
                    }
                    write_CRT_Temp(currentTemp);
                    oldSetTemp = setTemp;
                    oldCurrTemp = currentTemp;
                }
            }
            if (KeyPad_Get_Hash()){
                if (machineState == STANDBY){
                    write_State(OPERATIONAL);
                    SetMachineState(OPERATIONAL);
                } else {
                    write_State(STANDBY);
                    SetMachineState(STANDBY);
                }
            }
        }
    }
}

void config(){
    Activate_LCD();
    display_Welcome_screen(1);
    InitCalibrator();
    SystemPeriodicity_Init();
    KeyPad_Init();
}