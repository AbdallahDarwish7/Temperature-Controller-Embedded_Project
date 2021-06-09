/**
 * Created by abdallah drwesh
 */

#ifndef EMBEDDED_FINAL_PROJECT_CALIBRATOR_RESISTOR_H
#define EMBEDDED_FINAL_PROJECT_CALIBRATOR_RESISTOR_H

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "typedefs.h"

/*******************************************************************************
 *                               Defines                                        *
 *******************************************************************************/

#define CALIBRATOR_CHANNEL ((uint8)0)

/*******************************************************************************
 *                         Variables Declaration                               *
 *******************************************************************************/

extern float calibratorRead;

/*******************************************************************************
 *                         Functions Declaration                               *
 *******************************************************************************/

void InitCalibrator();
void UpdateCalibratorRead();

#endif //EMBEDDED_FINAL_PROJECT_CALIBRATOR_RESISTOR_H

