/*
 * ADC.c
 *
 * Created: 7/29/2025 6:27:39 PM
 *  Author: Zyad Ayman
 */ 
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"


static void (*g_ADC_Callback)(u16) = NULL;



void ADC_vInit(const ADC_Config_t* config)
{
	
	
	/************* Reference Voltage Configuration *************/
	// Clear REFS0 and REFS1 bits
	CLR_PIN(ADMUX, REFS0);
	CLR_PIN(ADMUX, REFS1);

	if (config->ref == ADC_REF_AREF)
	{
		// Already cleared ? AREF, internal Vref turned off
	}
	else if (config->ref == ADC_REF_AVCC)
	{
		SET_PIN(ADMUX, REFS0); // AVCC with external capacitor at AREF pin
	}
	else if (config->ref == ADC_REF_INTERNAL)
	{
		SET_PIN(ADMUX, REFS0);
		SET_PIN(ADMUX, REFS1); // Internal 2.56V with external capacitor
	}

	/************* Result Adjustment Configuration *************/
	if (config->adjust == ADC_LEFT_ADJUST)
	SET_PIN(ADMUX, ADLAR);
	else
	CLR_PIN(ADMUX, ADLAR);

	/************* Prescaler Setup *************/
	// Clear prescaler bits
	ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));

	switch (config->prescaler)
	{
		case ADC_PRESCALER_2:
		ADCSRA |= (1 << ADPS0);
		break;
		case ADC_PRESCALER_4:
		ADCSRA |= (1 << ADPS1);
		break;
		case ADC_PRESCALER_8:
		ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
		break;
		case ADC_PRESCALER_16:
		ADCSRA |= (1 << ADPS2);
		break;
		case ADC_PRESCALER_32:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
		break;
		case ADC_PRESCALER_64:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
		break;
		case ADC_PRESCALER_128:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		break;
	}

	/************* Auto Trigger *************/
	if (config->auto_trigger)
	SET_PIN(ADCSRA, ADATE);
	else
	CLR_PIN(ADCSRA, ADATE);
	
	
	/************* Interrupt Enable *************/
	if (config->interrupt_enable)
	{
		SET_PIN(ADCSRA, ADIE); // Enable ADC interrupt
		
	}
	else
	{
		CLR_PIN(ADCSRA, ADIE);
	}

	/************* Enable ADC *************/
	SET_PIN(ADCSRA, ADEN);
}




u16 ADC_u16Read_Value(u8 ADC_Channel)
{
	DIO_vSet_Pin_Direction('A', ADC_Channel, INPUT);

	/* Select ADC channel (0 to 7) */
	ADC_Channel &= 0x07;
	ADMUX = (ADMUX & 0xF8) | ADC_Channel;

	/* Start conversion */
	ADC_vStart_Conv();

	/* Wait for conversion complete */
	while (READ_PIN(ADCSRA, ADIF) == 0);

	/* Clear the flag */
	SET_PIN(ADCSRA, ADIF);

	_delay_us(10);

	return ADC;
}

/************************************************************************/
/*							Callback Setter                             */
/************************************************************************/






void ADC_SetCallback(void (*callback)(u16))
{
	g_ADC_Callback = callback;
}


/************************************************************************/
/*								ISR                                     */
/************************************************************************/


ISR(ADC_vect)
{
	if (g_ADC_Callback != NULL)
	{
		u16 result = ADC;
		g_ADC_Callback(result);
	}
}










