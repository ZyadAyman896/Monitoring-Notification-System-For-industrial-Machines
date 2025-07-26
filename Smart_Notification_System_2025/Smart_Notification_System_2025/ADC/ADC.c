/*
 * ADC.c
 *
 * Created: 2/14/2024 9:55:21 PM
 *  Author: Zyad Ayman
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "ADC.h"
#include "../DIO/DIO.h"
#include "../HELPING FILES/Utils.h"
#include <util/delay.h>





void ADC_vInit(void)
{
    /* Vref = AVCC with external capacitor at AREF pin, Right Adjust */
    ADMUX = (1 << REFS0); // REFS0 = 1, REFS1 = 0 → AVCC

    /* Enable ADC, Prescaler = F_CPU / 128 (62.5 KHz for 8 MHz CPU) */
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}


 
 u16 ADC_u16Read_Value(u8 ADC_Channel)
 {
	 /*	Make The Selected Channel As INPUT	*/	
	 DIO_vSet_Pin_Direction('A' , ADC_Channel , INPUT);

	 /* Select ADC channel (0 to 7) */
	 ADC_Channel &= 0x07;           /*	Mask to valid range	*/ 
	 ADMUX = (ADMUX & 0xF8) | ADC_Channel;
 
	 /* Start conversion */
	 ADC_vStart_Conv();
 
	 /* Wait for conversion to complete */
	 while (READ_PIN(ADCSRA, ADIF) == 0);
 
	 /* Clear the interrupt flag */
	 SET_PIN(ADCSRA, ADIF);
 
	 /* Small delay */
	 _delay_us(10);
 
	 return ADC; // Return ADC value
 }
 