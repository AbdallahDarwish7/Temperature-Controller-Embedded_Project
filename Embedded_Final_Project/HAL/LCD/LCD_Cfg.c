#include "LCD_Cfg.h"
const LCD_ConfigParamType LCD_ConfigParam = {
	/*LCD Configuration*/
	3, /*LCD Control Port*/
    0, /*LCD RS  DIO channel*/
	1, /*LCD RW  DIO channel*/
	2, /*LCD ENABLE  DIO channel*/
	2, /*LCD Data Port*/
    {
        0,1,2,3,4,5,6,7 /*LCD data0 DIO groups*/
    }
};
    
