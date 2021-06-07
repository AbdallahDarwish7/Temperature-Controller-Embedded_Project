//
// Created by abdulla167 on ٦‏/٦‏/٢٠٢١.
//
#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "PWM.h"
#include "Scheduler.h"


machine_state machineState = STANDBY;

uint8 CheckHeaterResponseFlag = 0;


static void UpdateSystem(machine_state state);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void InitSystem(){
    PeriodicDelay_ms(200, UpdateCurrentTemp);
}

void SetMachineState(machine_state state){
    if (machineState != ERROR){
        UpdateSystem(machineState);
    }
}

machine_state GetMachineState(){
    return machineState;
}

static void UpdateSystem(machine_state state){
    int8 DutyCycle;
    switch (state) {
        case STANDBY:
        {
            if (machineState != STANDBY){
                StopPeriodicDelay_ms(UpdateCurrentTemp);
                Shutdown_TC72();
                PWM_Stop();
                machineState = STANDBY;
            }
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
                if (CheckHeaterResponseFlag == 0){
                    CheckHeaterResponseFlag = 1;
                    Delay_ms(180000, CheckHeaterResponse);
                }
            } else{
                if (machineState != OPERATIONAL){
                    Activate_TC72();
                    StartPeriodicDelay_ms(UpdateCurrentTemp);
                    machineState = OPERATIONAL;
                }
                DutyCycle = CalculateDutyCycle(CurrentTemp, SetTemp);
                PWM_SetDutyCycle(DutyCycle, PWM_PHASE_CORRECT_MODE, PWM_NON_INVERTED_OC);
                PWM_Start();
            }
            break;
        }
        case NORMAL:
        {
            if (machineState != NORMAL){
                PWM_Stop();
            }
            break;
        }
        case ERROR:
        {
            StopPeriodicDelay_ms(UpdateCurrentTemp);
            Shutdown_TC72();
            PWM_Stop();
            break;
        }
    }
}

void CheckHeaterResponse(){
    CheckHeaterResponseFlag = 0;
    if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

float CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp){
    float Vt = 0;
    // Get Vr from callibrator resistor
    float Vr = 0;
    float DutyCycle = 0;
    if (SetTemp > CurrentTemp){
       Vt = ((SetTemp - CurrentTemp) / 100) * 10;
    }
    DutyCycle = (((Vr * 2) / 10) * Vt) / 10;
    return (int8)DutyCycle;
}

