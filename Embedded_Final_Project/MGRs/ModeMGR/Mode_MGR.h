//
// Created by abdulla167 on ٦‏/٦‏/٢٠٢١.
//

#ifndef EMBEDDED_FINAL_PROJECT_MODE_MGR_H
#define EMBEDDED_FINAL_PROJECT_MODE_MGR_H

#include <typedefs.h>

#define STANDBY ((uint8)0)
#define OPERATIONAL ((uint8)1)
#define NORMAL  ((uint8)2)
#define ERROR   ((uint8)3)

typedef uint8 machine_state;


int8 CalculateDutyCycle(int8 CurrentTemp, int8 SetTemp);
#endif //EMBEDDED_FINAL_PROJECT_MODE_MGR_H
