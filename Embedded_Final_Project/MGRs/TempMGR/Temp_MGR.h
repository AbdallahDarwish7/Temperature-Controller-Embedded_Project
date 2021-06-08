/*
* Created by abdulla167
*/


#ifndef EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
#define EMBEDDED_FINAL_PROJECT_TEMP_MGR_H

#define NO_READ ((int8)-128)

extern int8 currentTemp;
extern int8 setTemp;

/*******************************************************************************
 *                      Functions Declarations                                 *
 *******************************************************************************/

void UpdateInputTemp(int8 InputTemp);
void UpdateCurrentTemp(void);
void UpdateSetTemp(int8 InputTemp);
void Deactivate_TC72();
void Activate_TC72(void);

#endif /*EMBEDDED_FINAL_PROJECT_TEMP_MGR_H*/
