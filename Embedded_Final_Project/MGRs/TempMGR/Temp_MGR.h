/*
* Created by abdulla167
*/


#ifndef EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
#define EMBEDDED_FINAL_PROJECT_TEMP_MGR_H

#define NO_READ ((uint8)-1)

extern uint8 currentTemp;
extern uint8 setTemp;

/*******************************************************************************
 *                      Functions Declarations                                 *
 *******************************************************************************/

void UpdateCurrentTemp(void);
void UpdateInputTemp(uint8 InputTemp);
void Deactivate_TC72();
void Activate_TC72(void);
void TempMGR_Init();

#endif /*EMBEDDED_FINAL_PROJECT_TEMP_MGR_H*/
