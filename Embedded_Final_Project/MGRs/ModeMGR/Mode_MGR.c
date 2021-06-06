//
// Created by abdulla167 on ٦‏/٦‏/٢٠٢١.
//

#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "Timer.h"

machine_state machineState = STANDBY;

void ChangeMachineState(machine_state state){
    machineState = state;
}

machine_state GetMachineState(){
    return machineState;
}

void UpdateSystem(machine_state state){
    int8 DutyCycle;
    int8 CurrentTemp = GetCurrentTemp();
    int8 SetTemp = GetInputTemp();
    switch (state) {
        case STANDBY:
        {
            Shutdown_TC72();
            Timer_Stop(0);
            break;
        }
        case OPERATIONAL:
        {
            if (((CurrentTemp > SetTemp) && ((CurrentTemp - SetTemp) <= 5)) || ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) <= 5))){
                machineState = NORMAL;
                UpdateSystem(machineState);
            } else if ((CurrentTemp > SetTemp) && ((CurrentTemp - SetTemp) > 10)){
                machineState = ERROR;
                UpdateSystem(machineState);
            } else if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
                // Call Timer to execute method to check on condition again
            } else{
                // pass function to timer to call every 200 msec
                DutyCycle = CalculateDutyCycle(CurrentTemp, SetTemp);
            }
            break;
        }
        case NORMAL:
        {
            // Call Timer to execute method to check on condition again
            break;
        }
        case ERROR:
        {
            Shutdown_TC72();
            Timer_Stop(0);
            break;
        }
    }
}

void CheckHeaterResponse(){
    int8 CurrentTemp = GetCurrentTemp();
    int8 SetTemp = GetInputTemp();
    if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

//int8 CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp){
//    float Vt = 0;
//    float DutyCycle = 0;
//    if (SetTemp > CurrentTemp){
//       Vt = ((SetTemp - CurrentTemp) / 100) * 10;
//    }
//    // Get Vr from callibrator resistor
//    DutyCycle = (((Vr * 2) / 10) * Vt) / 10;
//    return (int8)DutyCycle;
//}

