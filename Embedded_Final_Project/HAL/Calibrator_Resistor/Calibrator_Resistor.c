/**
 * Created by abdallah drwesh on 6/7/21.
 */

#include "Calibrator_Resistor.h"
#include "ADC.h"

float calibratorRead = 20;

void InitCalibrator(){
    Init_ADC();
}

void UpdateCalibratorRead(){
    calibratorRead = ADC_Read(CALIBRATOR_CHANNEL);
}

