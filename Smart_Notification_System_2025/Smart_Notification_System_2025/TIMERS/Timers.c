/*
 * Timers.c
 *
 * Created: 7/20/2025 11:42:44 PM
 *  Author: Zyad Ayman
 */ 
#include <stdio.h>
#include <avr/interrupt.h>
#include "../Helping Files/std_types.h"
#include "../Helping Files/Utils.h"
#include "Timers.h"


/************************************************************************/
/*                        Variables                                     */
/************************************************************************/

/*	Pointer pointing to the callback Function of the Overflow Mode	*/
void( *g_OVF_Callback_Ptr )(void);



/*	Pointer pointing to the callback Function of the CTC Mode	*/
void( *g_COMPA_Callback_Ptr )(void);



/************************************************************************/
/*                        Timers API'S                                  */
/************************************************************************/


void TIMER1_vInit(const Timer1_Configurations* Config)
{
	
	/*	Setting mode of timer1		*/
	
	if( (*Config).Mode == TIMER1_MODE_NORMAL)
	{
		TCCR1A &= ~((1 << WGM10) | (1 << WGM11));  /* Clear WGM10/11					*/
		TCCR1B &= ~((1 << WGM12) | (1 << WGM13));  /* Normal mode: WGM13:0 = 0000		*/
		
	}
	else if ((*Config).Mode == TIMER1_MODE_CTC)
	{
		TCCR1A &= ~((1 << WGM10) | (1 << WGM11));  /* Clear WGM10/11							*/
		TCCR1B &= ~(1 << WGM13);                   /* Clear WGM13								*/
		TCCR1B |=  (1 << WGM12);                   /* Set WGM12 ? CTC mode (WGM13:0 = 0100)		*/

	}

	/*	Setting Initial Timer value		*/	
	TCNT1 = 0;  

	
	/*	Setting Mode of Interrupt	*/
	
	if((*Config).Interrupt_timer1 == TIMER1_INTERRUPT_ENABLED)
	{
		if((*Config).Mode == TIMER1_MODE_NORMAL)
		{
			TIMSK |= (1 << TOIE1);     /* Enable overflow interrupt		*/
		}
		else if((*Config).Mode == TIMER1_MODE_CTC)
		{
			TIMSK |= (1 << OCIE1A);    /* Enable Output Compare A Match interrupt	*/
		}
	}
	else if((*Config).Interrupt_timer1 == TIMER1_INTERRUPT_DISABLED)
	{
		TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));  /* Disable both	*/
	}
	

	
}





void TIMER1_vStart(Timer1_Prescalers Prescaler_Value)
{
	/* Clear the prescaler bits (CS12, CS11, CS10)	*/
    TCCR1B &= ~( (1 << CS12) | (1 << CS11) | (1 << CS10) );

    /* Set the new prescaler value	*/
    TCCR1B |= Prescaler_Value;
}

void TIMER1_vStop(void)
{
	TCCR1B &= 0xF8;  /* Clear CS12, CS11, CS10	*/
}


void TIMER1_vSetValueNormalMode(u16 value) 
{
	TCNT1 = value;
}



void TIMER1_vSetValueCompareCTC(u16 value) 
{
	OCR1A = value;
}


u16 TIMER1_u16GetValue(void)
{
	return TCNT1;
}

/************************************************************************/
/*                        Callback Setters                              */
/************************************************************************/


void TIMER1_vSetOverflowCallback( void (*callback_Ptr)(void) ) 
{
	g_OVF_Callback_Ptr = callback_Ptr;
}


void TIMER1_vSetCompareCTCCallback( void (*callback_Ptr)(void) ) 
{
	g_COMPA_Callback_Ptr = callback_Ptr;
}


/************************************************************************/
/*                        ISR Handlers                                  */
/************************************************************************/


ISR(TIMER1_OVF_vect) 
{
	if ( g_OVF_Callback_Ptr != NULL ) 
	{
		g_OVF_Callback_Ptr();	
	}
}

ISR(TIMER1_COMPA_vect) 
{
	if (g_COMPA_Callback_Ptr != NULL )
	{
		g_COMPA_Callback_Ptr();	
	} 
}



