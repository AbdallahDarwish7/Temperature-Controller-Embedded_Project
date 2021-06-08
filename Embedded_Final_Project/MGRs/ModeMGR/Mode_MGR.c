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

void InitSystemPeriodicity(){
    PeriodicDelay_ms(200, UpdateCurrentTemp);
    PeriodicDelay_ms(500, GetCalibratorRead);
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
                StopPeriodicDelay_ms(UpdateCurrentTemp);
                StopPeriodicDelay_ms(GetCalibratorRead);
                Shutdown_TC72();
                PWM_Stop();
                machineState = STANDBY;
            }
            break;
        }
        case OPERATIONAL:
        {
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
            } else{
                if (machineState != OPERATIONAL){
                    Activate_TC72();
                    StartPeriodicDelay_ms(UpdateCurrentTemp);
                    StartPeriodicDelay_ms(GetCalibratorRead);
                    machineState = OPERATIONAL;
                }
                DutyCycle = CalculateDutyCycle(currentTemp, setTemp, calibratorRead);
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
            StopPeriodicDelay_ms(GetCalibratorRead);
            Shutdown_TC72();
            PWM_Stop();
            break;
        }
        default :
            break;
    }
}

void CheckHeaterResponse(){
    CheckHeaterResponseFlag = 0;
    if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

float CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp, uint8 CalibratorRead){
    float Vt = 0;
    float DutyCycle = 0;
    if (SetTemp > CurrentTemp){
       Vt = ((SetTemp - CurrentTemp) / 100) * 10;
    }
    DutyCycle = (((CalibratorRead * 2) / 10) * Vt) / 10;
    return (int8)DutyCycle;
}

