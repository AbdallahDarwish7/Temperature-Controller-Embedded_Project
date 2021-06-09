
/*******************************************************************************
 *                             Includes                                        *
 *******************************************************************************/

#include <avr/io.h>
#include "ADC.h"
#include "DIO.h"

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/

void ADC_Init(uint8 channel) {
    DIO_ChannelDir(0, channel, 0);
    ADMUX |= (1 << REFS0);    /* Voltage Reference From VCC */
    ADCSRA |= (1 << ADEN);      /* Turn On ADC */
    ADCSRA |= (1 << ADSC);      /* Start Conversion */
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));  /*Setting the prescaler, choosing a division factor = 128, make the lowest frequency but highest accuracy = 16MHz / 128 = 125KHz*/
}


uint16 ADC_Read(uint8 channel) {
    ADMUX &= 0xF0;            /* Clear the old reading from the channel */
    ADMUX |= channel;        /* Defines the new ADC channel to be read */
    ADCSRA |= (1 << ADSC);  /* Start a new conversion */
    while (ADCSRA & (1 << ADSC));    /* Wait until the conversion is done */
    return ADC;
}
