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


/******************** Initializing System Periodicity ***********************
 * Function:  SystemPeriodicity_Init 
 * --------------------
 * used to passing the periodic functions to the timer array to be called when needed by appropriate delay :
 *                 
 */
void SystemPeriodicity_Init(void){
    PeriodicDelay_ms(200, &UpdateCurrentTemp);
    PeriodicDelay_ms(500, &UpdateCalibratorRead);
    PeriodicDelay_ms(100, &UpdateDutyCycle);
}


/******************** Setting System State ***********************
 * Function:  SetMachineState 
 * --------------------
 * used to update the states of system which are {STANDBY, OPERATIONAL, NORMAL, ERROR}:
 *
 *  state: System mode to be updated.
 * 
 */
void SetMachineState(MachineStateType state){
     UpdateSystem(state);
}


/******************** Getting System State ***********************
 * Function:  GetMachineState 
 * --------------------
 * used to indicate the current state of the system:
 *
 *  returns: the current system state.
 */
MachineStateType GetMachineState(void){
    return machineState;
}


/******************** Writing Port Data ***********************
 * Function:  UpdateSystem 
 * --------------------
 * used to update the system with the set state and execute each state conditions:
 *		STANDBY State: means system is not operational, no temperature reading and no
 *					   Voltage module control (PWM output is 0).
 *
 *		OPERATIONAL State: System shall read the current temperature periodically every
 *						    200ms.
 *
 *		NORMAL State: Periodic temperature reading is exist with voltage V = 0.
 *
 *		Error State: No temperature read and no PWM to voltage module control.
 *
 *  State: System mode to be updated.
 *
 */
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


/******************** Activating System ***********************
 * Function:  ActivateSystem 
 * --------------------
 * used to activate system components:
 *		Activating TC72 Temperature Sensor
 *		Activating PWM "pulse width modulation"
 *		Starting periodic Callback of Functions (UpdateCurrentTemp, 
 *														UpdateCalibratorRead, UpdateDutyCycle)  
 */
void ActivateSystem(void){
    Activate_TC72();
    PWM_Start();
    StartPeriodicDelay_ms(&UpdateCurrentTemp);
    StartPeriodicDelay_ms(&UpdateCalibratorRead);
    StartPeriodicDelay_ms(&UpdateDutyCycle);
}


/******************** Deactivating System ***********************
 * Function:  DeactivateSystem 
 * --------------------
 * used to deactivate system components:
 *		Deactivating TC72 Temperature Sensor
 *		Deactivating PWM "pulse width modulation"
 *		Stop periodic delay of the Functions (UpdateCurrentTemp,
 *														UpdateCalibratorRead, UpdateDutyCycle)
 */         
 
void DeactivateSystem(void){
    Deactivate_TC72();
    PWM_Stop();
    StopPeriodicDelay_ms(&UpdateCurrentTemp);
    StopPeriodicDelay_ms(&UpdateCalibratorRead);
    StopPeriodicDelay_ms(&UpdateDutyCycle);
}


/******************** Checking response of heater ***********************
 * Function:  CheckHeaterResponse 
 * --------------------
 * used to check if Set temperature > Current temperature and (Set temperature – Current temperature) > 5 
 *		for more than 3 minutes, system shall enter Error state.:
 *		Update System with the new Error State
 *
 */
void CheckHeaterResponse(void){
    checkHeaterResponseFlag = 0;
    if ((setTemp > currentTemp) && ((setTemp - currentTemp) > 5)){
        machineState = ERROR;
        UpdateSystem(machineState);
    }
}


/******************** Writing Port Data ***********************
 * Function:  UpdateDutyCycle 
 * --------------------
 * used to calculate the duty cycle in operational state by Calculating Vt and get Vr (from Calibration resistor) :
 *		get Vt According to these conditions:
 *					if (setTemp > currentTemp) : Vt = ((Set temperature – Current Temperature) / 100) * 10 
 *					else : Vt = 0
 *
 *		calculate DutyCycle = (((Vr * 2)/10) * Vt) / 10.
 *
 *		Passing DutyCycle to PWM function.
 */
void UpdateDutyCycle(void){
    float32 Vt = 0;
    if (setTemp > currentTemp){
       Vt = ((((float32)setTemp - (float32)currentTemp) / 100.0f) * 10.0f);
    }
    float32 DutyCycle = ((((calibratorRead * 2.0f) / 10.0f) * Vt) / 10.0f) * 100;
    PWM_SetDutyCycle(DutyCycle, PWM_PHASE_CORRECT_MODE, PWM_NON_INVERTED_OC);
}
