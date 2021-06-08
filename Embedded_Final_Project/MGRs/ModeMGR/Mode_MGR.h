/*
* Created by abdulla167
*/

#ifndef EMBEDDED_FINAL_PROJECT_MODE_MGR_H
#define EMBEDDED_FINAL_PROJECT_MODE_MGR_H

#include <typedefs.h>

#define STANDBY ((uint8)0)
#define OPERATIONAL ((uint8)1)
#define NORMAL  ((uint8)2)
#define ERROR   ((uint8)3)

typedef uint8 machine_state;

extern machine_state machineState;

machine_state GetMachineState(void);
void SetMachineState(machine_state state);
void SystemPeriodicity_Init(void);
void UpdateDutyCycle(void);
void CheckHeaterResponse(void);

#endif /*EMBEDDED_FINAL_PROJECT_MODE_MGR_H*/