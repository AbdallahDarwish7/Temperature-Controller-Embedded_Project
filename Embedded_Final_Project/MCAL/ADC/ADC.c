
/*******************************************************************************
 *                             Includes                                        *
 *******************************************************************************/

#include <avr/io.h>
#include "ADC.h"
#include "DIO.h"

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/
/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
void ADC_Init(uint8 channel) {
    DIO_ChannelDir(0U, channel, 0U);
    ADMUX = (uint8)(ADMUX | (uint8)(1U << (uint8)REFS0));    /* Voltage Reference From VCC */
    ADCSRA = (uint8)(ADCSRA | (uint8)(1U << (uint8)ADEN));      /* Turn On ADC */
    ADCSRA = (uint8)(ADCSRA | (uint8)(1U << (uint8)ADSC));      /* Start Conversion */
    ADCSRA = (uint8)(ADCSRA | (uint8)((uint8)(1U << (uint8)ADPS2) | (uint8)(1U << (uint8)ADPS1) | (uint8)(1U<< (uint8)ADPS0)));  /*Setting the prescaler, choosing a division factor = 128, make the lowest frequency but highest accuracy = 16MHz / 128 = 125KHz*/
}

/* JUSTIFICATION: may be unavoidable when addressing memory mapped registers or other hardware specific features*/
uint16 ADC_Read(uint8 channel) {
    ADMUX = (uint8)(ADMUX & 0xF0U);            /* Clear the old reading from the channel */
    ADMUX = (uint8)(ADMUX | channel);        /* Defines the new ADC channel to be read */
    ADCSRA = (uint8)(ADCSRA | (uint8)(1U << (uint8)ADSC));  /* Start a new conversion */
    while ((uint8)(ADCSRA & (uint8)(1U << (uint8)ADSC))){}    /* Wait until the conversion is done */
    return ADC;
}
