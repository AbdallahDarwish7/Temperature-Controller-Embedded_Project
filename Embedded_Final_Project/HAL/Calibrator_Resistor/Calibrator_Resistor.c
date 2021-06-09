/**
 * Created by abdallah drwesh
 */

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "Calibrator_Resistor.h"
#include "ADC.h"

/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/

float calibratorRead = 20;

/*******************************************************************************
 *                          Functions Definition                               *
 *******************************************************************************/

void InitCalibrator(){
    ADC_Init(CALIBRATOR_CHANNEL);
}

void UpdateCalibratorRead(){
    float temp = ((float )ADC_Read(CALIBRATOR_CHANNEL) / 1023.0f) * 5.0f;
    calibratorRead = temp;
}

