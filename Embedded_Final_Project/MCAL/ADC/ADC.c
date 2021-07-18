
/*******************************************************************************
 *                             Includes                                        *
 *******************************************************************************/

#include <avr/io.h>
#include "ADC.h"
#include "DIO.h"
#include "Macros.h"

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/
/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
void ADC_Init(uint8 channel) {
    DIO_ChannelDir(0U, channel, 0U);
    /* Voltage Reference From VCC */
    ADMUX = (uint8)(ADMUX | (uint8)(1U << (uint8)REFS0));
    /* Turn On ADC */
    ADCSRA = (uint8)(ADCSRA | (uint8)(1U << (uint8)ADEN));
    /*Setting the prescaler, choosing a division factor = 128, make the lowest frequency but highest accuracy = 16MHz / 128 = 125KHz*/
    ADCSRA = (uint8)(ADCSRA | (uint8)((uint8)(1U << (uint8)ADPS2) | (uint8)(1U << (uint8)ADPS1) | (uint8)(1U<< (uint8)ADPS0)));
}

/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
uint16 ADC_Read(uint8 channel) {
    /* Clear the old reading from the channel */
    ADMUX = (uint8)(ADMUX & 0xF0U);
    /* Defines the new ADC channel to be read */
    ADMUX = (uint8)(ADMUX | channel);
    /* Start a new conversion */
    ADCSRA = (uint8)(ADCSRA | (uint8)(1U << (uint8)ADSC));
    /* Wait until the conversion is done */
    while (BIT_IS_CLEAR(ADCSRA, ADIF) == 1U){}
    /*Clear ADIF*/
    SET_BIT(ADCSRA, ADIF);
    return ADC;
}
