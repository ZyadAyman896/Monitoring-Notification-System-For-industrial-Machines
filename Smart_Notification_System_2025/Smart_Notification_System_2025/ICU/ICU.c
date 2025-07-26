/*
 * ICU.c
 *
 * Created: 7/14/2025 10:00:56 AM
 *  Author: Zyad Ayman
 */ 
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "../Helping Files/Utils.h"
#include "../Helping Files/std_types.h"
#include "ICU.h"
#include "../DIO/DIO.h"


/************************************************************************/
/*                        Notes			                                
*You have to implement callback function - to be assigned to the ISR - in the main.
*
*
**************************************************************************/





/*	hold the address of the callback function in the application	*/
static volatile void(*g_ICU_Callback)(void) = NULL;


/*	ICU Interrupt	*/
ISR(TIMER1_CAPT_vect)
{
	
	
	if (g_ICU_Callback != NULL)
	{
		(*g_ICU_Callback)();
	}
	
	
	
	
}

void ICU_Init(ICU_EdgeType edge)
{
	/*	Setting PIN6 in PORTD As Input	*/
	DIO_vSet_Pin_Direction('d',PIN_NO_6,INPUT);
	
	/*	Set Timer Mode in Normal Mode	*/
	TCCR1A = 0x00 ;
	TCCR1B = 0x00 ; 


	/*	Prescaler = 8  */
	TCCR1B |= (1 << CS11);

	/*	Set Edge ( Rising / Falling )	*/
	ICU_SetEdge(edge);

	/* Initial Value for Timer1 */
	TCNT1 = 0 ;
	
	/* Initial Value for the input capture register */
	ICR1 = 0 ;
		
	/*	Enable ICU Interrupt	*/
	ICU_EnableInterrupt();
	 
}







void ICU_SetEdge(ICU_EdgeType edge)
{
	/* Set Edge ( Rising / Falling )	*/
	if(edge == ICU_RISING_EDGE)
	{
		TCCR1B |= (1 << ICES1) ;
	}
	else if (edge == ICU_FALLING_EDGE)
	{
		TCCR1B &= ~(1 << ICES1) ;
	}	
	
}




void ICU_EnableInterrupt(void)
{
	/*	Enable ICU Interrupt	*/
	SET_PIN(TIMSK , TICIE1);
}




void ICU_DisableInterrupt(void)
{
	/*	Disable ICU Interrupt	*/
	CLR_PIN(TIMSK , TICIE1);
}





void ICU_SetCallback( void(*ICU_Callback)(void) )
{
	g_ICU_Callback = ICU_Callback ;
}





u16 ICU_GetValue(void)
{
	
	return ICR1 ;
	
}

