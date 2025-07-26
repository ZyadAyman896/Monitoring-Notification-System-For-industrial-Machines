/*
 * PWM_Timer1.h
 *
 * Created: 2/11/2024 9:56:17 PM
 *  Author: Zyad Ayman
 */ 


#ifndef PWM_TIMER1_H_
#define PWM_TIMER1_H_


/************************************************************************/
/*                        #INCLUDES                                    */
/************************************************************************/

#include "../DIO/DIO.h"

/************************************************************************/
/*               Bit Numbers for Timer1 Control Registers               */
/************************************************************************/
/*  TCCR1A Register */ 
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define WGM11  1
#define WGM10  0

/*  TCCR1B Register */ 
#define ICNC1  7
#define ICES1  6
#define WGM13  4
#define WGM12  3
#define CS12   2
#define CS11   1
#define CS10   0

/************************************************************************/
/*                        CONFIGURATIONS                                */
/************************************************************************/

typedef enum {
    PWM_NO_CLK ,
    PWM_NO_PRESCALER,
    PWM_PRESCALE_8,
    PWM_PRESCALE_64,
    PWM_PRESCALE_256,
    PWM_PRESCALE_1024,
    PWM_EXTERNAL_CLK_FALL,
    PWM_EXTERNAL_CLK_RISING
} PWM_Prescaler;



typedef enum {
    FAST_EIGHT_BITS,
    FAST_NINE_BITS,
    FAST_TEN_BITS,
    FAST_TOP_OCR1A,
    FAST_TOP_ICR1
} PWM_FastModeType;



typedef enum {
    PHASE_EIGHT_BITS = 9,
    PHASE_NINE_BITS,
    PHASE_TEN_BITS,
    PHASE_TOP_OCR1A,
    PHASE_TOP_ICR1,
    PHASE_FREQ_TOP_OCR1A,
    PHASE_FREQ_TOP_ICR1
} PWM_PhaseModeType;


typedef enum {
	PWM_DISCONNECTED = 0,
	PWM_TOGGLE,           // Only works in some modes
	PWM_NON_INVERTING,
	PWM_INVERTING
} PWM_OutputMode;



/************************************************************************/
/*                        REGISTERS                                    */
/************************************************************************/

/*  TIMERS    */
#define  TIMSK *((volatile u8*)0x59)
#define  TIFR *((volatile u8*)0x58)



/*  TIMER0  */ 

#define TCCR0 *((volatile u8*)0x53)
#define TCNT0 *((volatile u8*)0x52)
#define OCR0 *((volatile u8*)0x5C)

/*  TIMER1  */

/*  Timer/Counter1 Control Register A ? TCCR1A */
#define	TCCR1A	*((volatile u8*)0x4F)

/*  Timer/Counter1 Control Register B ? TCCR1B    */
#define	TCCR1B	*((volatile u8*)0x4E)

/*  Timer/Counter1 ? TCNT1H and TCNT1L  */
#define	TCNT1L	*((volatile u8*)0x4C)

#define	TCNT1H *((volatile u8*)0x4D)

#define	TCNT1 *((volatile u16*)0x4C)

/*  Output Compare Register 1 A ? OCR1AH and OCR1AL   */
#define	OCR1AL *((volatile u8*)0x4A)
#define	OCR1AH *((volatile u8*)0x4B)
#define	OCR1A *((volatile u16*)0x4A)

/*  Output Compare Register 1 B ? OCR1BH and OCR1BL */
#define	OCR1BL *((volatile u8*)0x48)
#define	OCR1BH *((volatile u8*)0x49)
#define	OCR1B *((volatile u16*)0x48)

/*  Input Capture Register 1 ? ICR1H and ICR1L    */
#define	ICR1L *((volatile u8*)0x46)
#define	ICR1H *((volatile u8*)0x47)
#define	ICR1 *((volatile u16*)0x46)


/************************************************************************/
/*                        PWM TIMER1                                    */
/************************************************************************/


/**
 * brief: Set Output Compare Value for OC1A (Channel A)
 * param: copy_u16Value The compare match value to load into OCR1A
 */
void PWM_vSetValue_OCR1A_T1(u16 copy_u16Value);

/**
 * brief: Set Output Compare Value for OC1B (Channel B)
 * param: copy_u16Value The compare match value to load into OCR1B
 */
void PWM_vSetValue_OCR1B_T1(u16 copy_u16Value);

/**
 * brief: Set TOP value for Timer1 using ICR1 register
 * param: copy_u16Value The TOP value for PWM period control
 */
void PWM_vSetValue_ICR1_T1(u16 copy_u16Value);

/**
 * brief: Initialize Timer1 in Fast PWM mode with configurable settings
 * note : This must be called before setting OCR1A/B or ICR1
 * param: prescaler Timer1 clock prescaler bits (e.g., (1<<CS11)|(1<<CS10))
 * param: outputMode COM1A/B bits for output behavior (non-inverting/inverting)
 * param: topValue   Value for ICR1 to define the PWM period
 */
void PWM_vInit_T1_Fast(PWM_Prescaler prescaler, PWM_FastModeType mode, PWM_OutputMode OC1A_mode, PWM_OutputMode OC1B_mode, u16 topValue);



/**
 * brief: Initialize Timer1 in Phase Correct PWM mode with configurable settings
 * note : Use this if you want symmetric up-down counting waveform
 * param: prescaler Timer1 clock prescaler bits (e.g., (1<<CS11))
 * param: outputMode COM1A/B bits for output behavior (non-inverting/inverting)
 * param: topValue   Value for ICR1 to define the PWM period (top of counting)
 */
void PWM_vInit_T1_Phase(PWM_Prescaler prescaler, PWM_PhaseModeType mode, PWM_OutputMode OC1A_mode, PWM_OutputMode OC1B_mode, u16 topValue);







#endif /* PWM_Timer1.h */