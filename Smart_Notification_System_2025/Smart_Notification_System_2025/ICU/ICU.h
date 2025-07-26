/*
 * ICU.h
 *
 * Created: 7/14/2025 10:01:13 AM
 *  Author: Zyad Ayman
 */ 


#ifndef ICU_H_
#define ICU_H_

#include "../Helping Files/std_types.h"

/************************************************************************/
/*                        Variables			                            */
/************************************************************************/


/*	enum for edge types of signals		*/

typedef enum 
{
	ICU_RISING_EDGE ,
	ICU_FALLING_EDGE
		
} 
ICU_EdgeType;


/************************************************************************/
/*                        Functions Prototypes                          */
/************************************************************************/

void ICU_Init(ICU_EdgeType edge);

void ICU_SetEdge(ICU_EdgeType edge);

void ICU_EnableInterrupt(void);

void ICU_DisableInterrupt(void);

void ICU_SetCallback( void(*ICU_Callback)(void) );

u16 ICU_GetValue(void);



/************************************************************************/
/*                        Registers			                            */
/************************************************************************/



/* Timer/Counter1 Control Register A (TCCR1A)	*/
#define TCCR1A   (*(volatile u8*)0x4F)

/* Timer/Counter1 Control Register B (TCCR1B)	*/
#define TCCR1B   (*(volatile u8*)0x4E)

/* Timer/Counter1 (16-bit)	*/
#define TCNT1    (*(volatile u16*)0x4C)

/* Input Capture Register 1 (16-bit)	*/
#define ICR1     (*(volatile u16*)0x46)

/* Timer Interrupt Mask Register (TIMSK)	*/
#define TIMSK    (*(volatile u8*)0x59)

/* Timer Interrupt Flag Register (TIFR)		*/
#define TIFR     (*(volatile u8*)0x58)


/* Status Register (SREG) — for global interrupt enable/disable		*/
#define SREG     (*(volatile u8*)0x5F)


/* ========== Bit Definitions ========== */

/* TCCR1B bits	*/
#define ICES1    6   /* Input Capture Edge Select	*/
#define CS12     2   /* Clock Select bit 2	*/
#define CS11     1   /* Clock Select bit 1	*/
#define CS10     0   /* Clock Select bit 0	*/

/* TIMSK bits	*/
#define TICIE1   5   /* Timer/Counter1 Input Capture Interrupt Enable	*/

/* TIFR bits	*/

#define ICF1     5   /* Input Capture Flag	*/

/* SREG bits	*/
#define I_BIT    7   /* Global Interrupt Enable bit		*/



#endif /* ICU_H_ */