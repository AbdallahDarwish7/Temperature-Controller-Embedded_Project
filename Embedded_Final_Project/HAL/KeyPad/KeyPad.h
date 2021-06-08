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
void get_set_Temp_w(void);

uint8 pressed_Key(void);

void second_number(void);

void enter(void);

void get_set_Temp(ParamCallback callback);

uint8 get_Hash(void);

void Initialize_KeyPad(void);

void test_KeyPad_Lcd(void);

#endif /* KEYPAD_H_ */