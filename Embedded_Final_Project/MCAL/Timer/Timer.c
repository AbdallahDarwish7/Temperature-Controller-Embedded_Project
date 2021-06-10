/**
 * Created by abdallah drwesh on 6/2/21.
 */
#include "Timer.h"
#include <avr/io.h>

#define TIMER_1_REG ((uint8) 0U)
#define TIMER_2_REG ((uint8) 1U)

#define NUM_TIMERS_1_REG ((uint8) 2U)
#define NUM_TIMERS_2_REG ((uint8) 1U)

#define NUM_TIMER0_PRESCALERS  ((uint8) 5U)
#define TIMER0_PRESCALER_MASK ((uint8) 0xF8)
#define NUM_TIMER0_MODES  ((uint8) 4U)
#define TIMER0_MODES_MASK ((uint8) 0xB7)
#define NUM_TIMER0_COM ((uint8) 3U)
#define TIMER0_COM_MASK ((uint8) 0xCF)

#define NUM_TIMER1_PRESCALERS  ((uint8) 5U)
#define TIMER1_PRESCALER_MASK ((uint16) 0xF8FF)
#define NUM_TIMER1_MODES  ((uint8) 15U)
#define TIMER1_MODES_MASK ((uint16) 0xE7FC)

#define NUM_TIMER2_PRESCALERS  ((uint8) 7U)
#define TIMER2_PRESCALER_MASK ((uint8) 0xF8)
#define NUM_TIMER2_MODES  ((uint8) 4U)
#define TIMER2_MODES_MASK ((uint8) 0xB7)
#define NUM_TIMER2_COM ((uint8) 3U)
#define TIMER2_COM_MASK ((uint8) 0xCF)


#define TIMERS1REG_STOP_MASK (TIMER0_PRESCALER_MASK)
#define TIMERS2REG_STOP_MASK (TIMER1_PRESCALER_MASK)

uint8 TimersRegMode[NUM_TIMERS] = {TIMER_1_REG, TIMER_2_REG, TIMER_1_REG};
uint8 Timers1RegIds[NUM_TIMERS_1_REG] = {0, 2};
uint8 Timers2RegIds[NUM_TIMERS_2_REG] = {1};

uint8 Timers1RegPrescalersNum[NUM_TIMERS_1_REG] = {NUM_TIMER0_PRESCALERS, NUM_TIMER2_PRESCALERS};
uint8 Timers1RegPrescalerMask[NUM_TIMERS_1_REG] = {TIMER0_PRESCALER_MASK, TIMER2_PRESCALER_MASK};
uint8 Timers1RegModesNum[NUM_TIMERS_1_REG] = {NUM_TIMER0_MODES, NUM_TIMER2_MODES};
uint8 Timers1RegModesMask[NUM_TIMERS_1_REG] = {TIMER0_MODES_MASK, TIMER2_MODES_MASK};
uint8 Timers1RegComNum[NUM_TIMERS_1_REG] = {NUM_TIMER0_COM, NUM_TIMER2_COM};
uint8 Timers1RegComsMask[NUM_TIMERS_1_REG] = {TIMER0_COM_MASK, TIMER2_COM_MASK};


uint8 Timers2RegPrescalersNum[NUM_TIMERS_2_REG] = {NUM_TIMER1_PRESCALERS};
uint16 Timers2RegPrescalerMask[NUM_TIMERS_2_REG] = {TIMER1_PRESCALER_MASK};
uint8 Timers2RegModesNum[NUM_TIMERS_2_REG] = {NUM_TIMER1_MODES};
uint16 Timers2RegModesMask[NUM_TIMERS_2_REG] = {TIMER1_MODES_MASK};

/* Timer 0 */
uint16 Timer0Prescalers[NUM_TIMER0_PRESCALERS] = {1, 8, 64, 256, 1024};
uint8 Timer0PrescalersRegValues[NUM_TIMER0_PRESCALERS] = {0x01, 0x02, 0x03, 0x04, 0x05};

uint8 Timer0Modes[NUM_TIMER0_MODES] = {TIMER_NORMAL_MODE, TIMER_CTC_MODE, TIMER_PWD_PHASE_CORRECT_MODE,
                                       TIMER_PWD_FAST_MODE};
uint8 Timer0ModesRegValues[NUM_TIMER0_MODES] = {0x00, 0x08, 0x40, 0x48};

uint8 Timer0Coms[NUM_TIMER0_COM] = {TIMER_DISCONCTED_COM, TIMER_NON_INVERTED_COM, TIMER_INVERTED_COM};
uint8 Timer0ComsRegValues[NUM_TIMER0_COM] = {0x00, 0x20, 0x30};

/* Timer 1 */
uint16 Timer1Prescalers[NUM_TIMER1_PRESCALERS] = {1, 8, 64, 256, 1024};
uint16 Timer1PrescalersRegValues[NUM_TIMER1_PRESCALERS] = {0x0100, 0x0200, 0x0300, 0x0400, 0x0500};

uint8 Timer1Modes[NUM_TIMER1_MODES] = {TIMER_NORMAL_MODE, TIMER_CTC_MODE, TIMER_PWD_PHASE_CORRECT_MODE,
                                       TIMER_PWD_FAST_MODE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                       0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

uint16 Timer1ModesRegValues[NUM_TIMER1_MODES] = {0x0000, 0x0800, 0x0040, 0x0048, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                                 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/* Timer 2 */
uint16 Timer2Prescalers[NUM_TIMER2_PRESCALERS] = {1, 8, 32, 64, 128, 256, 1024};
uint8 Timer2PrescalersRegValues[NUM_TIMER2_PRESCALERS] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

uint8 Timer2Modes[NUM_TIMER2_MODES] = {TIMER_NORMAL_MODE, TIMER_CTC_MODE, TIMER_PWD_PHASE_CORRECT_MODE,
                                       TIMER_PWD_FAST_MODE};
uint8 Timer2ModesRegValues[NUM_TIMER2_MODES] = {0x00, 0x08, 0x40, 0x48};

uint8 Timer2Coms[NUM_TIMER2_COM] = {TIMER_DISCONCTED_COM, TIMER_NON_INVERTED_COM, TIMER_INVERTED_COM};
uint8 Timer2ComsRegValues[NUM_TIMER2_COM] = {0x00, 0x20, 0x30};

uint16 *Timers1RegPrescalersPtr[NUM_TIMERS_1_REG] = {Timer0Prescalers, Timer2Prescalers};
uint16 *Timers2RegPrescalersPtr[NUM_TIMERS_2_REG] = {Timer1Prescalers};

uint8 *Timers1RegPrescalersRegValuesPtr[NUM_TIMERS_1_REG] = {Timer0PrescalersRegValues, Timer2PrescalersRegValues};
uint16 *Timers2RegPrescalersRegValuesPtr[NUM_TIMERS_2_REG] = {Timer1PrescalersRegValues};

uint8 *Timers1RegModesPtr[NUM_TIMERS_1_REG] = {Timer0Modes, Timer2Modes};
uint8 *Timers2RegModesPtr[NUM_TIMERS_2_REG] = {Timer1Modes};

uint8 *Timers1RegModesRegValuesPtr[NUM_TIMERS_1_REG] = {Timer0ModesRegValues, Timer2ModesRegValues};
uint16 *Timers2RegModesRegValuesPtr[NUM_TIMERS_2_REG] = {Timer1ModesRegValues};

uint8 *Timers1RegComsPtr[NUM_TIMERS_1_REG] = {Timer0Coms, Timer2Coms};
/*uint16 *Timers2RegComsPtr[NUM_TIMERS_2_REG] = {Timer1Prescalers};*/

uint8 *Timers1RegComsRegValuesPtr[NUM_TIMERS_1_REG] = {Timer0ComsRegValues, Timer2ComsRegValues};
/*uint16 *Timers2RegComsRegValuesPtr[NUM_TIMERS_2_REG] = {Timer1Prescalers};*/


/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
volatile uint8 *TCCRs1[NUM_TIMERS_1_REG] = {&TCCR0, &TCCR2};
/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
volatile uint8 *TCCRs2[NUM_TIMERS_2_REG * 2U] = {&TCCR1A, &TCCR1B};
/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
volatile uint8 *OCRs[NUM_TIMERS_1_REG] = {&OCR0, &OCR2};

void Timer_Init(uint8 TimerId, uint8 TimerMode, uint8 TimerCom) {
    if (TimerId < NUM_TIMERS) {
        uint8 Loop;
        uint8 TimerIndex = 0;
        if (TimersRegMode[TimerId] == TIMER_1_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_1_REG; Loop++) {
                if (Timers1RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            uint8 *Timer1RegModes = Timers1RegModesPtr[TimerIndex];
            uint8 *Timer1RegModesRegValues = Timers1RegModesRegValuesPtr[TimerIndex];
            uint8 *Timer1RegComs = Timers1RegComsPtr[TimerIndex];
            uint8 *Timer1RegComsRegValues = Timers1RegComsRegValuesPtr[TimerIndex];
            uint8 Modes1RegNum = Timers1RegModesNum[TimerIndex];
            uint8 Coms1RegNum = Timers1RegComNum[TimerIndex];
            uint8 Timer1RegModeRegValue = 0x00;
            uint8 Timer1RegComRegValue = 0x00;
            for (Loop = 0U; Loop < Modes1RegNum; Loop++) {
                /* JUSTIFICATION: Modes1RegNum get the right length of array and not out of boundary indexing*/
                if (Timer1RegModes[Loop] == TimerMode) {
                    Timer1RegModeRegValue = Timer1RegModesRegValues[Loop];
                }
            }
            *(TCCRs1[TimerIndex]) &= Timers1RegModesMask[TimerIndex];
            *(TCCRs1[TimerIndex]) |= Timer1RegModeRegValue;
            for (Loop = 0U; Loop < Coms1RegNum; Loop++) {
                /* JUSTIFICATION: Coms1RegNum get the right length of array and not out of boundary indexing*/
                if (Timer1RegComs[Loop] == TimerCom) {
                    Timer1RegComRegValue = Timer1RegComsRegValues[Loop];
                }
            }
            *(TCCRs1[TimerIndex]) &= Timers1RegComsMask[TimerIndex];
            *(TCCRs1[TimerIndex]) |= Timer1RegComRegValue;

        } else if (TimersRegMode[TimerId] == TIMER_2_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_2_REG; Loop++) {
                if (Timers2RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            uint8 *Timer2RegModes = Timers2RegModesPtr[TimerIndex];
            uint16 *Timer2RegModesRegValues = Timers2RegModesRegValuesPtr[TimerIndex];
            uint8 Modes2RegNum = Timers2RegModesNum[TimerIndex];
            uint16 Timer2RegModeRegValue = 0x0000;
            for (Loop = 0U; Loop < Modes2RegNum; Loop++) {
                /* JUSTIFICATION: Modes2RegNum get the right length of array and not out of boundary indexing*/
                if (Timer2RegModes[Loop] == TimerMode) {
                    Timer2RegModeRegValue = Timer2RegModesRegValues[Loop];
                }
            }
            *(TCCRs2[TimerIndex]) = *(TCCRs2[TimerIndex]) & (uint8) Timers2RegModesMask[TimerIndex];
            *(TCCRs2[TimerIndex + 1U]) = *(TCCRs2[TimerIndex + 1U]) & (uint8) (Timers2RegModesMask[TimerIndex] >> 8U);
            *(TCCRs2[TimerIndex]) = *(TCCRs2[TimerIndex]) | (uint8) Timer2RegModeRegValue;
            *(TCCRs2[TimerIndex + 1U]) = *(TCCRs2[TimerIndex + 1U]) | (uint8) (Timer2RegModeRegValue >> 8U);
            /* TODO: Implementation Timer1 COM Modes*/
        } else {
            /*Timer not in the defined types*/
        }
    } else {
        /*Timer id > num of timers*/
    }
}

void Timer_Start(uint8 TimerId, uint16 TimerPreScaler) {
    if (TimerId < NUM_TIMERS) {
        /* JUSTIFICATION: local variables for the same meaning */
        uint8 Loop;
        uint8 TimerIndex = 0;
        if (TimersRegMode[TimerId] == TIMER_1_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_1_REG; Loop++) {
                if (Timers1RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            uint16 *Timer1RegPrescalers = Timers1RegPrescalersPtr[TimerIndex];
            uint8 *Timer1RegPrescalerRegValues = Timers1RegPrescalersRegValuesPtr[TimerIndex];
            uint8 Prescaler1RegNum = Timers1RegPrescalersNum[TimerIndex];
            uint8 Timer1RegPrescalerRegValue = 0x00;
            for (Loop = 0U; Loop < Prescaler1RegNum; Loop++) {
                /* JUSTIFICATION: Prescaler1RegNum get the right length of array and not out of boundary indexing*/
                if (Timer1RegPrescalers[Loop] == TimerPreScaler) {
                    Timer1RegPrescalerRegValue = Timer1RegPrescalerRegValues[Loop];
                }
            }
            *(TCCRs1[TimerIndex]) = *(TCCRs1[TimerIndex]) & Timers1RegPrescalerMask[TimerIndex];
            *(TCCRs1[TimerIndex]) = *(TCCRs1[TimerIndex]) | Timer1RegPrescalerRegValue;

        } else if (TimersRegMode[TimerId] == TIMER_2_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_2_REG; Loop++) {
                if (Timers2RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            uint16 *Timer2RegPrescalers = Timers2RegPrescalersPtr[TimerIndex];
            uint16 *Timer2RegPrescalerRegValues = Timers2RegPrescalersRegValuesPtr[TimerIndex];
            uint8 Prescaler2RegNum = Timers2RegPrescalersNum[TimerIndex];
            uint16 Timer2RegPrescalerRegValue = 0x00000;
            for (Loop = 0U; Loop < Prescaler2RegNum; Loop++) {
                /* JUSTIFICATION: Prescaler2RegNum get the right length of array and not out of boundary indexing*/
                if (Timer2RegPrescalers[Loop] == TimerPreScaler) {
                    Timer2RegPrescalerRegValue = Timer2RegPrescalerRegValues[Loop];
                }
            }
            *(TCCRs2[TimerIndex]) = *(TCCRs2[TimerIndex]) & (uint8) (Timers2RegPrescalerMask[TimerIndex]);
            *(TCCRs2[TimerIndex + 1U]) = *(TCCRs2[TimerIndex + 1U]) & (uint8) (Timers2RegPrescalerMask[TimerIndex] >> 8U);
            *(TCCRs2[TimerIndex]) = *(TCCRs2[TimerIndex]) | (uint8) Timer2RegPrescalerRegValue;
            *(TCCRs2[TimerIndex + 1U]) = *(TCCRs2[TimerIndex + 1U]) | (uint8) (Timer2RegPrescalerRegValue >> 8U);
        } else {
            /*Timer not in the defined types*/
        }
    } else {
        /*Timer id > num of timers*/
    }
}

void Timer_Stop(uint8 TimerId) {
    if (TimerId < NUM_TIMERS) {
        /* JUSTIFICATION: local variables for the same meaning */
        uint8 TimerIndex = 0;
        uint8 Loop;
        if (TimersRegMode[TimerId] == TIMER_1_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_1_REG; Loop++) {
                if (Timers1RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            *(TCCRs1[TimerIndex]) = *(TCCRs1[TimerIndex]) & TIMERS1REG_STOP_MASK;
        } else if (TimersRegMode[TimerId] == TIMER_2_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_2_REG; Loop++) {
                if (Timers2RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            *(TCCRs2[TimerIndex]) = *(TCCRs2[TimerIndex]) & (uint8) TIMERS2REG_STOP_MASK;
            *(TCCRs2[TimerIndex + 1U]) = *(TCCRs2[TimerIndex + 1U]) & (uint8) (TIMERS2REG_STOP_MASK >> 8U);
        } else {
            /*Timer not in the defined types*/
        }
    } else {
        /*Timer id > num of timers*/
    }
}

void Timer_SetDutyCycle(uint8 TimerId, float32 Percentage, uint8 TimerMode, uint8 TimerCom) {
    if (TimerId < NUM_TIMERS) {
        /* JUSTIFICATION: local variables for the same meaning */
        uint8 TimerIndex = 0;
        uint8 Loop;
        if (TimersRegMode[TimerId] == TIMER_1_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_1_REG; Loop++) {
                if (Timers1RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            uint8 regVal;
            if (TimerMode == TIMER_PWD_FAST_MODE) {
                if (TimerCom == TIMER_NON_INVERTED_COM) {
                    /* JUSTIFICATION: MicroController Registers can hold only unsigned char or char values and Value can't proceed 255*/
                    regVal = (uint8) (((256U * Percentage) / 100U) - 1U);
                    *(OCRs[TimerIndex]) = regVal;
                } else if (TimerCom == TIMER_INVERTED_COM) {
                    /* JUSTIFICATION: MicroController Registers can hold only unsigned char or char values and Value can't proceed 255*/
                    regVal = 255U - (uint8) (((256U * Percentage) / 100) - 1U);
                    *(OCRs[TimerIndex]) = regVal;
                } else {
                    /*No Default  Output Modes*/
                }
            } else if (TimerMode == TIMER_PWD_PHASE_CORRECT_MODE) {
                if (TimerCom == TIMER_NON_INVERTED_COM) {
                    /* JUSTIFICATION: MicroController Registers can hold only unsigned char or char values and Value can't proceed 255*/
                    regVal = (uint8) ((255U * Percentage) / 100U);
                    *(OCRs[TimerIndex]) = regVal;
                } else if (TimerCom == TIMER_INVERTED_COM) {
                    /* JUSTIFICATION: MicroController Registers can hold only unsigned char or char values and Value can't proceed 255*/
                    regVal = 255U - (uint8) ((255U * Percentage) / 100U);
                    *(OCRs[TimerIndex]) = regVal;
                } else {
                    /*No Default  Output Modes*/
                }
            } else {
                /* TODO: More Modes for Timers 2 registers */
            }
        } else {
            /*Timer not in the defined types*/
        }
    } else {
        /*Timer id > num of timers*/
    }
}

uint8 Timer_Is_Running(uint8 TimerId) {
    uint8 IsRunning = 0;
    if (TimerId < NUM_TIMERS) {
        /* JUSTIFICATION: local variables for the same meaning */
        uint8 TimerIndex = 0;
        uint8 Loop;
        if (TimersRegMode[TimerId] == TIMER_1_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_1_REG; Loop++) {
                if (Timers1RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
            IsRunning = (*(TCCRs1[TimerIndex]) & (uint8) (~TIMERS1REG_STOP_MASK));
        } else if (TimersRegMode[TimerId] == TIMER_2_REG) {
            for (Loop = 0U; Loop < NUM_TIMERS_2_REG; Loop++) {
                if (Timers2RegIds[Loop] == TimerId) {
                    TimerIndex = Loop;
                    break;
                }
            }
           /* IsRunning = *(TCCRs2[TimerIndex]) & (uint8)(~(uint8)TIMERS2REG_STOP_MASK);
            IsRunning = IsRunning + (*(TCCRs2[TimerIndex + 1U]) & (uint8)(~(uint8)(TIMERS2REG_STOP_MASK >> 8U)));*/
            IsRunning = *(TCCRs2[TimerIndex + 1U]) & 0x07U;
        } else {
            /*Timer not in the defined types*/
        }
    } else {
        /*Timer id > num of timers*/
    }
    return IsRunning;
}



