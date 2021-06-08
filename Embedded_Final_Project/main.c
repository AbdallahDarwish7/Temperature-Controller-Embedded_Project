/*
 * Embedded_Final_Project.c
 *
 * Created: 6/2/2021 3:01:44 PM
 * Author : AbdallahDrwesh
 */

#include "Timer.h"
#include "DIO.h"
#include "typedefs.h"
#include "Scheduler.h"
#include "Display_MGR.h"
#include "Mode_MGR.h"
#include "Temp_MGR.h"
#include "Calibrator_Resistor.h"
#include "avr/io.h"
#include "util/delay.h"
#include "Display_MGR.h"
#include "KeyPad.h"
#include "TC72.h"
#include "Calibrator_Resistor.h"
#include "ADC.h"


void config();

int main(void) {
    config();
    _delay_ms(4000);
    while (1) {

        write_CRT_Temp(30);
    }
}

void config(){
//    SystemPeriodicity_Init();
    ADC_Init(0);
//    KeyPad_Init();
    Activate_LCD();
    display_Welcome_screen(1);
}

