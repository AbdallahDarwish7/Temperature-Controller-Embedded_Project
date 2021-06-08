#include <avr/io.h>
#include "ADC.h"
#include "DIO.h"
#include "typedefs.h"

void Init_ADC(void) {
    ADMUX = ADMUX | (uint8) (1U << REFS0);    /* Voltage Reference From VCC */
    ADCSRA = ADCSRA | (uint8) (1U << ADEN);      /* Turn On ADC */
    ADCSRA = ADCSRA | (uint8) (1U << ADSC);      /* Start Conversion */
    ADCSRA = ADCSRA | (uint8) ((1U << ADPS2) | (1 << ADPS1) | (1
            << ADPS0));  /*Setting the prescaler, choosing a division factor = 128, make the lowest frequency but highest accuracy = 16MHz / 128 = 125KHz*/
}

uint16 ADC_Read(uint8 channel) {
    DIO_ChannelDir(0, channel, 0); /* setting portid to A , setting the chosen channel , setting its direction to input*/
    ADMUX &= 0xF0;            /* Clear the old reading from the channel */
    ADMUX |= channel;        /* Defines the new ADC channel to be read */
    ADCSRA |= (1 << ADSC);  /* Start a new conversion */
    while (ADCSRA & (1 << ADSC))    /* Wait until the conversion is done */
        return ADC;
}
