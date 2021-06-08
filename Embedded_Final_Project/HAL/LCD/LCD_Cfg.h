#ifndef LCD_CFG_H_INCLUDED
#define LCD_CFG_H_INCLUDED
#include "typedefs.h"
#define LCD_NUM_OF_DATA_PINS ((uint8)4)
typedef struct
{
	uint8 ControlPortId;
	uint8 RSPinChannel;
	uint8 RWPinChannel;
	uint8 EnablePinChannel;
	uint8 DataPortId;
	uint8 DataPinsChannel[LCD_NUM_OF_DATA_PINS];
}LCD_ConfigParamType;
extern const LCD_ConfigParamType LCD_ConfigParam;

#endif // LCD_CFG_H_INCLUDED


