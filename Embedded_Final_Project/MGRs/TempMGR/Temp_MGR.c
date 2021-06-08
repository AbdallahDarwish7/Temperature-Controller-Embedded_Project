/*
* Created by abdulla167
*/
#include "typedefs.h"
#include "TC72.h"
#include "Temp_MGR.h"


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

int8 currentTemp = NO_READ;
int8 setTemp = 25;

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/


/******************** GetCurrentTemp *********************
 * Used to get The temperature of the TC72 sensor
 * @return currentTemp : Temperature value
 */
void UpdateCurrentTemp(void){
    Mode TC72_Mode = GetTC72Mode();
    if (TC72_Mode == SHUTDOWN_MODE){
        currentTemp = NO_READ;
    } else{
        currentTemp = TC72_ReadTemperature();
    }
}

/******************** SetInputTemp ***********************
 * Save temperature value that we get from the user
 * @param InputTemp : Input temperature of the user
 */
void UpdateInputTemp(int8 InputTemp){
    setTemp = InputTemp;
}


/******************** Shutdown_TC72 ***********************
 * Config the TC72 sensor to the idle mode
 */
void Deactivate_TC72(){
    TC72_Init(SHUTDOWN_MODE);
}

/******************** Shutdown_TC72 ***********************
 * Config the TC72 sensor to the continuous mode
 */
void Activate_TC72(void){
    TC72_Init(CONTINUOUS_MODE);
}

