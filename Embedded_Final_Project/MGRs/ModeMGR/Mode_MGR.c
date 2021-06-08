/*
* Created by abdulla167
*/
#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "PWM.h"
#include "Scheduler.h"
#include "Calibrator_Resistor.h"


machine_state machineState = STANDBY;

uint8 CheckHeaterResponseFlag = 0;


static void UpdateSystem(machine_state state);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void SystemPeriodicity_Init(void){
    PeriodicDelay_ms(200, &UpdateCurrentTemp);
    PeriodicDelay_ms(500, &UpdateCalibratorRead);
    PeriodicDelay_ms(100, &UpdateDutyCycle);
}

void SetMachineState(machine_state state){
    if (machineState != ERROR){
        UpdateSystem(state);
    }
}

machine_state GetMachineState(void){
    return machineState;
}

static void UpdateSystem(machine_state state){
    float32 DutyCycle;
    switch (state) {
        case NORMAL:
        {
            if (machineState != NORMAL){
                PWM_Stop();
            }
            break;
        }
        case STANDBY:
        {
            if (machineState != STANDBY){
                StopPeriodicDelay_ms(&UpdateCurrentTemp);
                StopPeriodicDelay_ms(&UpdateCalibratorRead);
                StopPeriodicDelay_ms(&UpdateDutyCycle);
                Deactivate_TC72();
                PWM_Stop();
                currentTemp = NO_READ;
                setTemp = NO_READ;
                machineState = STANDBY;
            }
            break;
        }
        case OPERATIONAL:
        {
            if (machineState != OPERATIONAL) {
                Activate_TC72();
                PWM_Start();
                StartPeriodicDelay_ms(&UpdateCurrentTemp);
                StartPeriodicDelay_ms(&UpdateCalibratorRead);
                StartPeriodicDelay_ms(&UpdateDutyCycle);
                machineState = OPERATIONAL;
            }
            break;
        }
        case ERROR:
        {
            StopPeriodicDelay_ms(&UpdateCurrentTemp);
            StopPeriodicDelay_ms(&UpdateCalibratorRead);
            StopPeriodicDelay_ms(&UpdateDutyCycle);
            Deactivate_TC72();
            PWM_Stop();
            currentTemp = NO_READ;
            setTemp = NO_READ;
            break;
        }
        default :
        {
            break;
        }
    }
}

void CheckHeaterResponse(void){
    CheckHeaterResponseFlag = (uint8)0;
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
    float32 DutyCycle = (((calibratorRead * 2.0f) / 10.0f) * Vt) / 10.0f;
    PWM_SetDutyCycle(DutyCycle, PWM_PHASE_CORRECT_MODE, PWM_NON_INVERTED_OC);
}

