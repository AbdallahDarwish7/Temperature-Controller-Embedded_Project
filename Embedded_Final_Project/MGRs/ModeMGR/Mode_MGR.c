/*
* Created by abdulla167
*/
#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "PWM.h"
#include "Scheduler.h"
#include "Calibrator_Resistor.h"
#include "Display_MGR.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

MachineStateType machineState = STANDBY;
uint8 checkHeaterResponseFlag = 0;

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/

void SystemPeriodicity_Init(void){
    PeriodicDelay_ms(200, &UpdateCurrentTemp);
    PeriodicDelay_ms(500, &UpdateCalibratorRead);
    PeriodicDelay_ms(100, &UpdateDutyCycle);
}

void SetMachineState(MachineStateType state){
     UpdateSystem(state);
}

MachineStateType GetMachineState(void){
    return machineState;
}

void UpdateSystem(MachineStateType state){
    switch (state) {
        case NORMAL:
        {
            if (checkHeaterResponseFlag == 1){
                DeleteDelay_ms(&CheckHeaterResponse);
            }
            if (machineState != NORMAL){
                PWM_Stop();
            }
            machineState = NORMAL;
            write_State(NORMAL);
            break;
        }
        case STANDBY:
        {
            if (checkHeaterResponseFlag == 1){
                DeleteDelay_ms(&CheckHeaterResponse);
            }
            if (machineState != STANDBY){
                DeactivateSystem();
            }
            machineState = STANDBY;
            write_State(STANDBY);
            break;
        }
        case OPERATIONAL:
        {
            if ((machineState != OPERATIONAL) && (machineState != NORMAL)) {
               ActivateSystem();
               Delay_ms(MAX_TIME_OF_RESPONSE, CheckHeaterResponse);
            } else if (machineState == NORMAL){
                PWM_Start();
                Delay_ms(MAX_TIME_OF_RESPONSE, CheckHeaterResponse);
            }
            checkHeaterResponseFlag = 1;
            machineState = OPERATIONAL;
            write_State(OPERATIONAL);
            break;
        }
        case ERROR:
        {
            if (checkHeaterResponseFlag == 1){
                DeleteDelay_ms(&CheckHeaterResponse);
            }
            DeactivateSystem();
            machineState = ERROR;
            write_State(ERROR);
            break;
        }
        default :
        {
            break;
        }
    }
}

void ActivateSystem(void){
    Activate_TC72();
    PWM_Start();
    StartPeriodicDelay_ms(&UpdateCurrentTemp);
    StartPeriodicDelay_ms(&UpdateCalibratorRead);
    StartPeriodicDelay_ms(&UpdateDutyCycle);
}

void DeactivateSystem(void){
    Deactivate_TC72();
    PWM_Stop();
    StopPeriodicDelay_ms(&UpdateCurrentTemp);
    StopPeriodicDelay_ms(&UpdateCalibratorRead);
    StopPeriodicDelay_ms(&UpdateDutyCycle);
}

void CheckHeaterResponse(void){
    checkHeaterResponseFlag = 0;
    if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

void UpdateDutyCycle(void){
    float32 Vt = 0;
    if (setTemp > currentTemp){
       Vt = ((((float32)setTemp - (float32)currentTemp) / 100.0f) * 10.0f);
    }
    float32 DutyCycle = ((((calibratorRead * 2.0f) / 10.0f) * Vt) / 10.0f) * 100;
    PWM_SetDutyCycle(DutyCycle, PWM_PHASE_CORRECT_MODE, PWM_NON_INVERTED_OC);
}
