/*
 * LCD_Manager.h
 *
 * Created: 6/6/2021 6:45:16 PM
 *  Author: river
 */ 

#ifndef LCD_MANAGER_H_
#define LCD_MANAGER_H_
#include "LCD_Manager_cfg.h"
#include "typedefs.h"

void Shift_Right(void);

void Shift_Left(void);

void display_Welcome_screen(uint8 times);

void display_Welcome_once(void);

void idle_screen(void);

void write_State(STATES_ConfigParamType state);

void write_CRT_Temp(uint8 crt_temp);

void write_Set_Temp(uint8 set_temp);

void Initialize_LCD();

#endif /* LCD_MANAGER_H_ */