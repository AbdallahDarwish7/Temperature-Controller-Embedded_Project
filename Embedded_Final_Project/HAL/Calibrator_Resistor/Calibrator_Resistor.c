/**
 * Created by abdallah drwesh on 6/7/21.
 */

#include "Calibrator_Resistor.h"
#include "ADC.h"

uint8 calibratorRead = 0;

void InitCalibrator(){
    Init_ADC(0);
}

void GetCalibratorRead(){
    calibratorRead = (uint8)(ADC_Read(CALIBRATOR_CHANNEL) / 1024) * 5;
}

