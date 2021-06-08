/*
* Created by abdulla167
*/

#ifndef FINAL_PROJECT_MACROS_H
#define FINAL_PROJECT_MACROS_H

/*                ************** Justification *****************
 *                  Deviate from rule 19.7 (advisory)
 *                  This macro makes the code clearer and conciser
 */
#define BIT_IS_SET(PORT, BIT_NUM)    (((PORT) & (BIT_NUM)))
/*#define BIT_IS_CLEAR(PORT, BIT_NUM)  (((!((PORT)) & ((uint8)((uint8)1 << (BIT_NUM))))))*/
#define BIT_IS_CLEAR(PORT, BIT_NUM)  ( !((uint8)((PORT) & ((uint8)((uint8)1 << (BIT_NUM)))))  )


#define SET_BIT(PORT, BIT_NUM)       (((PORT) |= (uint8)((uint8)1 << (BIT_NUM))))

#define CLEAR_BIT(PORT, BIT_NUM)     ((PORT) = (uint8)((PORT) & ((uint8)(~((uint8)((uint8)1 << (BIT_NUM)))))))
#define NULL ((void*) 0 )
#endif /*FINAL_PROJECT_MACROS_H*/
