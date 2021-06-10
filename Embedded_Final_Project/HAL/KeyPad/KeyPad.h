/*
 * KeyPad.h
 *
 * Created: 6/2/2021 3:13:29 PM
 *  Author: Mohamed Kamal
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "typedefs.h"

#define NO_VALUE ((uint8)0xff)

uint8 KeyPad_GetKey(void);

uint8 KeyPad_GetKeyValue(uint8 key);

uint8 KeyPad_Get_Hash(void);

void KeyPad_Init(void);

#endif /* KEYPAD_H_ */
