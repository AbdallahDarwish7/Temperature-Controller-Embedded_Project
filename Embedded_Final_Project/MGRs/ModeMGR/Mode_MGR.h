/*
* Created by abdulla167
*/

#ifndef EMBEDDED_FINAL_PROJECT_MODE_MGR_H
#define EMBEDDED_FINAL_PROJECT_MODE_MGR_H

#include <typedefs.h>



/*******************************************************************************
 *                             Definitions                                     *
 *******************************************************************************/

#define STANDBY ((uint8)0)
#define OPERATIONAL ((uint8)1)
#define NORMAL  ((uint8)2)
#define ERROR   ((uint8)3)
#define MAX_TIME_OF_RESPONSE 10000

/*******************************************************************************
 *                                Typedefs                                     *
 *******************************************************************************/

typedef uint8 MachineStateType;

/*******************************************************************************
 *                           Functions Declarations                            *
 *******************************************************************************/

MachineStateType GetMachineState(void);
void SetMachineState(MachineStateType state);
void UpdateSystem(MachineStateType state);
void SystemPeriodicity_Init(void);
void UpdateDutyCycle(void);
void CheckHeaterResponse(void);
void ActivateSystem(void);
void DeactivateSystem(void);

#endif /*EMBEDDED_FINAL_PROJECT_MODE_MGR_H*/