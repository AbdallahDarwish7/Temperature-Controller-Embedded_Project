//
// Created by abdulla167 on ٢‏/٦‏/٢٠٢١.
//

#ifndef FINAL_PROJECT_MACROS_H
#define FINAL_PROJECT_MACROS_H


#define BIT_IS_SET(PORT, BIT_NUM) (PORT & BIT_NUM)
#define BIT_IS_CLEAR(PORT, BIT_NUM) (!(PORT & (1 << BIT_NUM)))
#define SET_BIT(PORT, BIT_NUM) (PORT |= (1 << BIT_NUM))
#define CLEAR_BIT(PORT, BIT_NUM) (PORT = PORT & (~(1 << BIT_NUM)))
#define NULL 0U
#endif //FINAL_PROJECT_MACROS_H
