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
        case STANDBY:
        {
            if (machineState != STANDBY){
                StopPeriodicDelay_ms(&UpdateCurrentTemp);
                StopPeriodicDelay_ms(&UpdateCalibratorRead);
                Deactivate_TC72();
                PWM_Stop();
                machineState = STANDBY;
            }
            break;
        }
        case OPERATIONAL:
        {
            if (machineState != OPERATIONAL) {
                Activate_TC72();
                StartPeriodicDelay_ms(&UpdateCurrentTemp);
                StartPeriodicDelay_ms(&UpdateCalibratorRead);
                machineState = OPERATIONAL;
            }
            DutyCycle = CalculateDutyCycle(currentTemp, setTemp, calibratorRead);
            PWM_SetDutyCycle(DutyCycle, PWM_PHASE_CORRECT_MODE, PWM_NON_INVERTED_OC);
            PWM_Start();
            if (((currentTemp > setTemp) && ((currentTemp - setTemp) <= 5)) || ((setTemp > currentTemp) && ((setTemp - currentTemp) <= 5))){
                machineState = NORMAL;
                UpdateSystem(machineState);
            } else if ((currentTemp > setTemp) && ((currentTemp - setTemp) > 10)){
                machineState = ERROR;
                UpdateSystem(machineState);
            } else if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5)){
                if (CheckHeaterResponseFlag == 0){
                    CheckHeaterResponseFlag = 1;
                    Delay_ms(180000, CheckHeaterResponse);
                }
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
            StopPeriodicDelay_ms(&UpdateCurrentTemp);
            StopPeriodicDelay_ms(&UpdateCalibratorRead);
            Deactivate_TC72();
            PWM_Stop();
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

float32 CalculateDutyCycle(int8 CurrentTemperature, int8 SetTemperature, uint8 CalibratorRead){
    float32 Vt = 0;
    if (SetTemperature > CurrentTemperature){
       Vt = ((((float32)SetTemperature - (float32)CurrentTemperature) / 100.0f) * 10.0f);
    }
    float32 Dutycycle = (((CalibratorRead * 2.0f) / 10.0f) * Vt) / 10.0f;
    return Dutycycle;
}

