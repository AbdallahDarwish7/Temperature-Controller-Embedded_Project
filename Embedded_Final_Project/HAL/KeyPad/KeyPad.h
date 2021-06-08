/*
 * KeyPad.h
 *
 * Created: 6/2/2021 3:13:29 PM
 *  Author: Mohamed Kamal
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "typedefs.h"
typedef void (*ParamCallback)(uint8);


void get_set_Temp_wrapper(void);

uint8 KeyPad_GetKey(void);

void KeyPad_Enter(void);

void get_set_Temp(ParamCallback callback);

uint8 KeyPad_Get_Hash(void);

void KeyPad_Initialize(void);

#endif /* KEYPAD_H_ */