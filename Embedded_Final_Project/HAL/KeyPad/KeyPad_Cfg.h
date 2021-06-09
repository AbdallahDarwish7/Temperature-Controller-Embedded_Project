#ifndef KeyPad_CFG_H_INCLUDED
#define KeyPad_CFG_H_INCLUDED
#include "typedefs.h"

#define KeyPad_NUM_OF_COLS_PINS ((uint8)3)
#define KeyPad_NUM_OF_RAW_PINS ((uint8)4)
typedef struct
{
	uint8 ColsPortId;
	uint8 ColsPinsChannels[KeyPad_NUM_OF_COLS_PINS];
	uint8 RowsPortId;
	uint8 RowsPinsChannels[KeyPad_NUM_OF_RAW_PINS];
}KeyPad_ConfigParamType;
extern const KeyPad_ConfigParamType KeyPad_ConfigParam;
#endif /* KeyPad_CFG_H_INCLUDED */


