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
<<<<<<< HEAD
void InitSystem(void){
    PeriodicDelay_ms(200, &UpdateCurrentTemp);
=======
void InitSystemPeriodicity(){
    PeriodicDelay_ms(200, UpdateCurrentTemp);
    PeriodicDelay_ms(500, GetCalibratorRead);
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
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
<<<<<<< HEAD
                StopPeriodicDelay_ms(&UpdateCurrentTemp);
=======
                StopPeriodicDelay_ms(UpdateCurrentTemp);
                StopPeriodicDelay_ms(GetCalibratorRead);
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
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
<<<<<<< HEAD
            } else if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
                if (CheckHeaterResponseFlag ==(uint8) 0){
                    CheckHeaterResponseFlag = (uint8)1;
                    Delay_ms((uint32)180000, &CheckHeaterResponse);
=======
            } else if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5)){
                if (CheckHeaterResponseFlag == 0){
                    CheckHeaterResponseFlag = 1;
                    Delay_ms(180000, CheckHeaterResponse);
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
                }
            } else{
                if (machineState != OPERATIONAL){
                    Activate_TC72();
<<<<<<< HEAD
                    StartPeriodicDelay_ms(&UpdateCurrentTemp);
=======
                    StartPeriodicDelay_ms(UpdateCurrentTemp);
                    StartPeriodicDelay_ms(GetCalibratorRead);
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
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
<<<<<<< HEAD
            StopPeriodicDelay_ms(&UpdateCurrentTemp);
=======
            StopPeriodicDelay_ms(UpdateCurrentTemp);
            StopPeriodicDelay_ms(GetCalibratorRead);
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
            Shutdown_TC72();
            PWM_Stop();
            break;
        }
        default :
            break;
    }
}

<<<<<<< HEAD
void CheckHeaterResponse(void){
    CheckHeaterResponseFlag = (uint8)0;
    if ((SetTemp > CurrentTemp) && ((SetTemp - CurrentTemp) > 5)){
=======
void CheckHeaterResponse(){
    CheckHeaterResponseFlag = 0;
    if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5)){
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}

<<<<<<< HEAD
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
=======
float CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp, uint8 CalibratorRead){
    float Vt = 0;
    float DutyCycle = 0;
    if (SetTemp > CurrentTemp){
       Vt = ((SetTemp - CurrentTemp) / 100) * 10;
    }
    DutyCycle = (((CalibratorRead * 2) / 10) * Vt) / 10;
    return (int8)DutyCycle;
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98
}

