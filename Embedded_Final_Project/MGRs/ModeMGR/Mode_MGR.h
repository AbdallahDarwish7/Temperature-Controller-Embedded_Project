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

<<<<<<< HEAD
machine_state GetMachineState(void);
void SetMachineState(machine_state state);
void InitSystem(void);
float32 CalculateDutyCycle(int8 CurrentTemperature, int8 SetTemperature);
void CheckHeaterResponse(void);
=======
void InitSystemPeriodicity();
float CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp, uint8 CalibratorRead);
void CheckHeaterResponse();
>>>>>>> 0111a4a3fe76d5859866b0f18c0a90e1c826ed98

#endif /*EMBEDDED_FINAL_PROJECT_MODE_MGR_H*/
