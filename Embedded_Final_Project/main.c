/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */


#include "Timer.h"
#include "DIO.h"

#include "Scheduler.h"
#include "LCD_Manager.h"
#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "Calibrator_Resistor.h"
#include "avr/io.h"
#include "util/delay.h"
#include "LCD_Manager.h"
#include "KeyPad.h"
#include "TC72.h"
#include "Calibrator_Resistor.h"
#include "ADC.h"


void config();

int main(void) {
//    Init_ADC();
config();
    while (1) {
//        SetMachineState(OPERATIONAL);
//        UpdateCalibratorRead();
        write_CRT_Temp((uint8)ADC_Read(0));
    }
}


void config(){
    Initialize_LCD();
    Init_ADC();
    display_Welcome_screen(0);
}
