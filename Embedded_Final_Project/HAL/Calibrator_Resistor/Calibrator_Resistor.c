/**
 * Created by abdallah drwesh
 */

#include "Calibrator_Resistor.h"
#include "ADC.h"

float calibratorRead = 20;

void InitCalibrator(){
    Init_ADC(CALIBRATOR_CHANNEL);
}

void UpdateCalibratorRead(){
    calibratorRead = (uint8)(ADC_Read(CALIBRATOR_CHANNEL) / 1024) * 5;
}

