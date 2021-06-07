/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */


#include "Timer.h"
#include "DIO.h"

#include "KeyPad.h"
#include "Scheduler.h"
#include "LCD_Manager.h"
#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "Calibrator_Resistor.h"
#include "avr/io.h"
#include "util/delay.h"
#include "LCD_Manager.h"
#include "KeyPad.h"


void config();

int main(void) {
    config();
    while (1) {}
}


void config(){
    Initialize_LCD();
    InitSystemPeriodicity();
    Activate_TC72();
    InitCalibrator();
    display_Welcome_screen(3);
}
