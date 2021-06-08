#ifndef ADC_H_
#define ADC_H_
#include "typedefs.h"


void ADC_Init(uint8 channel);
uint16 ADC_Read(uint8 channel);

#endif /* ADC_H_ */
