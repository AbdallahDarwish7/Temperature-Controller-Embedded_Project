/**
 * Created by abdallah drwesh on 6/7/21.
 */

#ifndef EMBEDDED_FINAL_PROJECT_CALIBRATOR_RESISTOR_H
#define EMBEDDED_FINAL_PROJECT_CALIBRATOR_RESISTOR_H
#include "typedefs.h"


#define CALIBRATOR_CHANNEL ((uint8)0)

extern uint8 calibratorRead;

void InitCalibrator();
void GetCalibratorRead();
#endif //EMBEDDED_FINAL_PROJECT_CALIBRATOR_RESISTOR_H
