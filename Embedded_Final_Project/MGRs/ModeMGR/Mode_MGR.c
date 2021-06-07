//
// Created by abdulla167 on ٦‏/٦‏/٢٠٢١.
//

#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "PWM.h"
#include "Scheduler.h"

machine_state machineState = STANDBY;

void ChangeMachineState(machine_state state){
    machineState = state;
}

machine_state GetMachineState(){
    return machineState;
}

void UpdateSystem(machine_state state){
    int8 DutyCycle;
    switch (state) {
        case STANDBY:
        {
            Shutdown_TC72();
            PWM_Stop();
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
                void (*CheckResponsePtr)(void) = CheckHeaterResponse;
                Delay_ms(180000, CheckResponsePtr);
            } else{
                void (* UpdateCurrentTempPtr)(void) = UpdateCurrentTemp;
                Periodic_Delay_ms(200, UpdateCurrentTempPtr);
                DutyCycle = CalculateDutyCycle(CurrentTemp, SetTemp);
                PWM_SetDutyCycle(DutyCycle, PWM_PHASE_CORRECT_MODE, PWM_NON_INVERTED_OC);
                PWM_Start();
            }
            break;
        }
        case NORMAL:
        {
            void (* UpdateCurrentTempPtr)(void) = UpdateCurrentTemp;
            Periodic_Delay_ms(200, UpdateCurrentTempPtr);
            break;
        }
        case ERROR:
        {
            Shutdown_TC72();
            PWM_Stop();
            break;
        }
    }
}

void CheckHeaterResponse(){
    if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

float CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp){
    float Vt = 0;
    float DutyCycle = 0;
    if (SetTemp > CurrentTemp){
       Vt = ((SetTemp - CurrentTemp) / 100) * 10;
    }
    // Get Vr from callibrator resistor
    DutyCycle = (((Vr * 2) / 10) * Vt) / 10;
    return (int8)DutyCycle;
}

