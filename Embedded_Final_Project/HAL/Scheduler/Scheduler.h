/**
 * Created by abdallah drwesh on 6/5/21.
 */

#ifndef EMBEDDED_FINAL_PROJECT_SCHEDULER_H
#define EMBEDDED_FINAL_PROJECT_SCHEDULER_H
#include "typedefs.h"

typedef void (*VoidCallback)(void);

void Delay_ms(uint32 Delay_ms, VoidCallback callback);

void Periodic_Delay_ms(int16 Delay_ms, VoidCallback callback);

void Stop_Periodic_Delay_ms(VoidCallback callback);

void Start_Periodic_Delay_ms(VoidCallback callback);

#endif //EMBEDDED_FINAL_PROJECT_SCHEDULER_H
