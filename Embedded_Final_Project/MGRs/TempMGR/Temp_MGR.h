/*
* Created by abdulla167
*/


#ifndef EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
#define EMBEDDED_FINAL_PROJECT_TEMP_MGR_H

/*******************************************************************************
 *                            Definition                                       *
 *******************************************************************************/

#define NO_READ ((uint8)-1)

/*******************************************************************************
 *                        Variables Declaration                                *
 *******************************************************************************/

extern uint8 currentTemp;
extern uint8 setTemp;

/*******************************************************************************
 *                         Type Definitions                                    *
 *******************************************************************************/

typedef void (*ParamCallback)(uint8 pram);

/*******************************************************************************
 *                         Functions Declarations                              *
 *******************************************************************************/

void GetSetTempConfig(ParamCallback callback);

void StopGetSetTemp(void);

void StartGetSetTemp(void);

void GetSetTempWrapper(void);

void UpdateCurrentTemp(void);

void UpdateInputTemp(uint8 InputTemp);

void Deactivate_TC72(void);

void Activate_TC72(void);

void TempMGR_Init(void);

#endif /*EMBEDDED_FINAL_PROJECT_TEMP_MGR_H*/
