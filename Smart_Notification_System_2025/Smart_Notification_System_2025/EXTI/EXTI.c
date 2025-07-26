/*
 * EXTI.c
 *
 * Created: 7/22/2025 7:57:34 PM
 *  Author: Zyad Ayman
 */ 
#include <stdio.h>
#include <avr/interrupt.h>
#include "EXTI.h"



/************************************************************************/
/*                        Global Variables                              */
/************************************************************************/

/*	Interrupt callback pointers for : EXTI0 , EXTI1 & EXTI2		*/

static void (*g_INT0_Callback)(void) = NULL;
static void (*g_INT1_Callback)(void) = NULL;
static void (*g_INT2_Callback)(void) = NULL;




/************************************************************************/
/*                          EXTI API'S                                  */
/************************************************************************/

void EXTI_vInit(u8 interrupt_number, EXTI_SenseMode sense_mode)
{
	switch(interrupt_number)
	{
		case EXTI_INT0:
		DDRD &= ~(1 << PD2);     /* Set PD2 as input	*/
		PORTD |= (1 << PD2);     /* Enable pull-up resistor	*/
		switch(sense_mode)
		{
			case EXTI_LOW_LEVEL:
			MCUCR &= ~((1 << ISC00) | (1 << ISC01)); /* 00	*/
			break;

			case EXTI_ANY_CHANGE:
			MCUCR &= ~(1 << ISC01);
			MCUCR |=  (1 << ISC00);                  /* 01	*/
			break;

			case EXTI_FALLING_EDGE:
			MCUCR |=  (1 << ISC01);
			MCUCR &= ~(1 << ISC00);                  /* 10	*/
			break;

			case EXTI_RISING_EDGE:
			MCUCR |= (1 << ISC00) | (1 << ISC01);    /* 11	*/
			break;
		}
		break;

		case EXTI_INT1:
		DDRD &= ~(1 << PD3);     /* Set PD3 as input	*/
		PORTD |= (1 << PD3);     /* Enable pull-up resistor	*/
		switch(sense_mode)
		{
			case EXTI_LOW_LEVEL:
			MCUCR &= ~((1 << ISC10) | (1 << ISC11)); /* 00	*/
			break;

			case EXTI_ANY_CHANGE:
			MCUCR &= ~(1 << ISC11);
			MCUCR |=  (1 << ISC10);                  /* 01	*/
			break;

			case EXTI_FALLING_EDGE:
			MCUCR |=  (1 << ISC11);
			MCUCR &= ~(1 << ISC10);                  /* 10	*/
			break;

			case EXTI_RISING_EDGE:
			MCUCR |= (1 << ISC10) | (1 << ISC11);    /* 11	*/
			break;
		}
		break;

		case EXTI_INT2:
		DDRB &= ~(1 << PB2);     /* Set PB2 as input	*/
		PORTB |= (1 << PB2);     /* Enable pull-up resistor	*/
		if (sense_mode == EXTI_FALLING_EDGE)
		{
			MCUCSR &= ~(1 << ISC2);                      /* 0	*/
		}
		else if (sense_mode == EXTI_RISING_EDGE)
		{
			MCUCSR |= (1 << ISC2);                       /* 1	*/
		}
		break;

		default:
		/* Optional: handle invalid interrupt number	*/
		break;
	}	
}


void EXTI_vEnable(u8 interrupt_number)
{
	switch (interrupt_number)
	{
		case EXTI_INT0:
		GICR |= (1 << INT0_EN_BIT);
		break;

		case EXTI_INT1:
		GICR |= (1 << INT1_EN_BIT);
		break;

		case EXTI_INT2:
		GICR |= (1 << INT2_EN_BIT);
		break;

		default:
		/* Optionally handle invalid interrupt number	*/
		break;
	}
}


void EXTI_vDisable(u8 interrupt_number)
{
	switch (interrupt_number)
	{
		case EXTI_INT0:
		GICR &= ~(1 << INT0_EN_BIT);
		break;

		case EXTI_INT1:
		GICR &= ~(1 << INT1_EN_BIT);
		break;

		case EXTI_INT2:
		GICR &= ~(1 << INT2_EN_BIT);
		break;

		default:
		/* Optionally handle invalid interrupt number	*/
		break;
	}
}





/************************************************************************/
/*                        Callback Setters                              */
/************************************************************************/




void EXTI_vSetCallback(u8 interrupt_number, void (*callback)(void))
{
	
	if (interrupt_number == 0)
	{
		g_INT0_Callback = callback ;
	} 
	else if(interrupt_number == 1)
	{
		g_INT1_Callback = callback ;
	}
	else if (interrupt_number == 2)
	{
		g_INT2_Callback = callback ;
	}
	
	
	
}






/************************************************************************/
/*                        ISR Handlers                                  */
/************************************************************************/




ISR(INT0_vect) 
{
	if (g_INT0_Callback != NULL) 
	{
		g_INT0_Callback();	
	}
	
}

ISR(INT1_vect) 
{
	
	if (g_INT1_Callback != NULL) 
	{
		g_INT1_Callback();	
	}
	
}

ISR(INT2_vect) 
{
	
	if (g_INT2_Callback != NULL) 
	{
		g_INT2_Callback();
	}
}

