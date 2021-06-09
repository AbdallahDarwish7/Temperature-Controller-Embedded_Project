/*
* Created by abdulla167
*/
#include "typedefs.h"
#include "TC72.h"
#include "Temp_MGR.h"


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

uint8 currentTemp = NO_READ;
uint8 setTemp = 25;

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/


/******************** Updating Temperature values ***********************
 * Function:  UpdateCurrentTemp 
 * --------------------
 * used to update the value of current temperature from TC72 sensor according to Sensor mode:
 *		SHUTDOWN_MODE : No temperature to be read
 *		At any other mode: read temperature from sensor and update CurrentTemp "Global Variable"
 *
 */
void UpdateCurrentTemp(void){
    Mode TC72_Mode = GetTC72Mode();
    if (TC72_Mode == SHUTDOWN_MODE){
        currentTemp = NO_READ;
    } else{
        currentTemp = TC72_ReadTemperature();
    }
}


/******************** Updating Temperature values ***********************
 * Function:  UpdateInputTemp 
 * --------------------
 * used to update the value of Set temperature from Keypad:
 *
 * InputTemp: The value of temperature written on the keypad
 *
 */
void UpdateInputTemp(uint8 InputTemp){
    setTemp = InputTemp;
}


/******************** Temperature Manager Initiation ***********************
 * Function:  TempMGR_Init 
 * --------------------
 * used to initiate TC72 sensor after power on and no temperature reading "SHUTDOWN_MODE".
 *
 */
void TempMGR_Init(){
    TC72_Init(SHUTDOWN_MODE);
}


/******************** Temperature Manager Deactivate TC72 ***********************
 * Function:  Deactivate_TC72 
 * --------------------
 * used to deactivate TC72 sensor by applying "SHUTDOWN_MODE".
 *
 */
void Deactivate_TC72(){
    if (GetTC72Mode() != SHUTDOWN_MODE){
        TC72_Mode(SHUTDOWN_MODE);
    }
}


/******************** Temperature Manager Deactivate TC72 ***********************
 * Function:  Deactivate_TC72 
 * --------------------
 * used to Config the TC72 sensor to the continuous mode.
 *
 */
void Activate_TC72(void){
    if (GetTC72Mode() != CONTINUOUS_MODE){
        TC72_Mode(CONTINUOUS_MODE);
    }
}

