/**
 * Created by abdallah drwesh
 */

#include "Calibrator_Resistor.h"
#include "ADC.h"

float calibratorRead = 20;

void InitCalibrator(){
    ADC_Init(CALIBRATOR_CHANNEL);
}

void UpdateCalibratorRead(){
    float temp = ((float )ADC_Read(CALIBRATOR_CHANNEL) / 1023.0f) * 5.0f;
    calibratorRead = temp;
}

