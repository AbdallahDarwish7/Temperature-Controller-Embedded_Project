//
// Created by abdulla167 on ٦‏/٦‏/٢٠٢١.
//


#ifndef EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
#define EMBEDDED_FINAL_PROJECT_TEMP_MGR_H

#define NO_READ ((int8)-128)


int8 GetCurrentTemp();

int8 GetInputTemp();

void SetInputTemp(int8 InputTemp);

void Shutdown_TC72();

void Activate_TC72();




#endif //EMBEDDED_FINAL_PROJECT_TEMP_MGR_H
