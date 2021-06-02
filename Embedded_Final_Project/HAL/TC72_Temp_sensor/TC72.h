//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//

#ifndef FINAL_PROJECT_TC72_H
#define FINAL_PROJECT_TC72_H
#include "SPI.h"

typedef uint8 Mode;

#define CONTINUOUS_MODE ((uint8)0x00)
#define ONE_SHOT_MODE ((uint8)0x05)
#define SHUTDOWN_MODE ((uint8)0x01)

void init(Mode operationMode);
uint8 ReadTemperature(void);

#endif //FINAL_PROJECT_TC72_H
