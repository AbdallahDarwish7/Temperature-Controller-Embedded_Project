/**
 * Created by abdallah drwesh on 6/7/21.
 */

#ifndef EMBEDDED_FINAL_PROJECT_PWD_H
#define EMBEDDED_FINAL_PROJECT_PWD_H
#include "typedefs.h"
#include "Timer.h"

/*******************************************************************************
 *                             PWM Modes                                       *
 *******************************************************************************/
#define PWM_PHASE_CORRECT_MODE (TIMER_PWD_PHASE_CORRECT_MODE)
#define PWM_FAST_MODE (TIMER_PWD_FAST_MODE)

/*******************************************************************************
 *                            Output Compare Modes                             *
 *******************************************************************************/
#define PWM_NON_INVERTED_OC (TIMER_NON_INVERTED_COM)
#define PWM_INVERTED_OC (TIMER_INVERTED_COM)

/*******************************************************************************
 *                         Functions Declarations                              *
 *******************************************************************************/

void PWM_SetDutyCycle(float Percentage, uint8 PwmMode, uint8 PwmOutputCompareMode);
void PWM_Start();
void PWM_Stop();




#endif //EMBEDDED_FINAL_PROJECT_PWD_H
