//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//
#ifndef FINAL_PROJECT_TC72_H
#define FINAL_PROJECT_TC72_H

#include "SPI.h"


/*******************************************************************************
 *                      TC72 Operation Modes                                  *
 *******************************************************************************/
typedef uint8 Mode;

#define CONTINUOUS_MODE ((uint8)0x00)
#define ONE_SHOT_MODE ((uint8)0x05)
#define SHUTDOWN_MODE ((uint8)0x01)

/*******************************************************************************
 *                      TC72 Registers Addresses                                 *
 *******************************************************************************/

#define Control_Register_Address ((uint8)0x80)
#define MSB_Register_Address ((uint8)0x02)
#define LSB_Register_Address ((uint8)0x01)


/*******************************************************************************
 *                      Functions Declarations                                  *
 *******************************************************************************/

void TC72_Init(Mode operationMode);
int8 TC72_ReadTemperature(void);
Mode GetTC72Mode();


#endif //FINAL_PROJECT_TC72_H
