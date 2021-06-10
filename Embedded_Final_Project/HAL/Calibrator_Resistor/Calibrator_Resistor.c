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

float32 calibratorRead = 20;

/*******************************************************************************
 *                          Functions Definition                               *
 *******************************************************************************/

void InitCalibrator(void){
    ADC_Init(CALIBRATOR_CHANNEL);
}

void UpdateCalibratorRead(void){
    float32 temp = ((float32 )ADC_Read(CALIBRATOR_CHANNEL) / 1023.0f) * 5.0f;
    calibratorRead = temp;
}

