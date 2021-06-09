/*
 * KeyPad.h
 *
 * Created: 6/2/2021 3:13:29 PM
 *  Author: Mohamed Kamal
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "typedefs.h"
typedef void (*ParamCallback)(uint8 pram);

#define NO_VALUE ((uint8)0xff)

uint8 KeyPad_GetKey(void);

void KeyPad_Enter(void);

void GetSetTempConfig(ParamCallback callback);

void StopGetSetTemp(void);

void StartGetSetTemp(void);

uint8 KeyPad_Get_Hash(void);

void KeyPad_Init(void);

#endif /* KEYPAD_H_ */
