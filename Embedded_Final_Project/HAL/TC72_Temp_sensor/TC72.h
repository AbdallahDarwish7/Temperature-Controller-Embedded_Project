/*
* Created by abdulla167
*/
#ifndef FINAL_PROJECT_TC72_H
#define FINAL_PROJECT_TC72_H

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "SPI.h"

/*******************************************************************************
 *                      TC72 Operation Modes                                  *
 *******************************************************************************/
typedef uint8 Mode;

#define CONTINUOUS_MODE ((uint8)0x10)
#define SHUTDOWN_MODE ((uint8)0x01)

/*******************************************************************************
 *                      TC72 Registers Addresses                                 *
 *******************************************************************************/

#define Control_Register_Address ((uint8)0x80)
#define MSB_Register_Address ((uint8)0x02)


/*******************************************************************************
 *                      Functions Declarations                                  *
 *******************************************************************************/

void TC72_Init(Mode OperMode);
int8 TC72_ReadTemperature(void);
Mode GetTC72Mode(void);
void TC72_Mode(Mode OperMode);

#endif /*FINAL_PROJECT_TC72_H*/
