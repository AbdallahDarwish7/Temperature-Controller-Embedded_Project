/*
* Created by abdulla167
*/
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
void InitSystem(void){
    PeriodicDelay_ms(200, &UpdateCurrentTemp);
}

void SetMachineState(machine_state state){
    if (machineState != ERROR){
        UpdateSystem(machineState);
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
                if (CheckHeaterResponseFlag ==(uint8) 0){
                    CheckHeaterResponseFlag = (uint8)1;
                    Delay_ms((uint32)180000, &CheckHeaterResponse);
                }
            } else{
                if (machineState != OPERATIONAL){
                    Activate_TC72();
                    StartPeriodicDelay_ms(&UpdateCurrentTemp);
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
            StopPeriodicDelay_ms(&UpdateCurrentTemp);
            Shutdown_TC72();
            PWM_Stop();
            break;
        }
        default :
            break;
    }
}

void CheckHeaterResponse(void){
    CheckHeaterResponseFlag = (uint8)0;
    if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

float32 CalculateDutyCycle(int8 CurrentTemperature, int8 SetTemperature){
    float32 Vt = 0;
    /* Get Vr from callibrator resistor*/
    float32 Vr = 0;
    /*float32 DutyCycle = 0;*/
    if (SetTemperature > CurrentTemperature){
       Vt = ((((float32)SetTemperature - (float32)CurrentTemperature) / 100.0f) * 10.0f);
    }
    float32 Dutycycle = (((Vr * 2.0f) / 10.0f) * Vt) / 10.0f;
    return Dutycycle;
}

