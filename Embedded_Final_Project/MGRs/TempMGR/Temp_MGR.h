//
// Created by abdulla167 on ٦‏/٦‏/٢٠٢١.
//


#ifndef EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
#define EMBEDDED_FINAL_PROJECT_TEMP_MGR_H

#define NO_READ ((int8)-128)

extern int8 currentTemp;
extern int8 setTemp;

/*******************************************************************************
 *                      Functions Declarations                                 *
 *******************************************************************************/
 
void UpdateCurrentTemp();

void UpdateSetTemp(int8 InputTemp);

void Shutdown_TC72();

void Activate_TC72();




#endif //EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
