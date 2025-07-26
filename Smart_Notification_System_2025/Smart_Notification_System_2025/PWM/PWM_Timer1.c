/*
 * PWM_ICU_WDT.c
 *
 * Created: 2/11/2024 9:56:03 PM
 *  Author: Zyad Ayman
 */ 

/************************************************************************/
/*                        HOW TO .....?                                    */
/************************************************************************/


/*
	*	HOW TO USE THIS DRIVER FOR PWM 
	*	FIRST THING ==> SETTING PRESCALER FOR T0 OR T1 OR T2 
	*	SECOND THING ==> CHOOSING THE MODE IF IT IS 1-(FAST PWM) 2-(PHASE CORRECT PWM ) 
	*	THIRD THING ==>  
	*	***FOR FAST PWM***
	*	TAKE CARE OF THE FREQUENCY EQN 
	*	YOU HAVE 5 MODES 8BIT OR 9BIT OR 10BIT OR FAST OR FAST
	*	BUT TAKE CARE FROM WHERE THE TOP WILL BE LOADED 
	*	YOU HAVE 3 OPTIONS FOR THE TOP 1==> FIXED VALUES 2==>YOU LOAD IT MANUALLY IN ICR1 3==>YOU LOAD IT MANUALLY IN OCR1A
	*	*NOTE* == > YOU DETERMINE THE VALUE OF THE TOP IF YOU WANT TO CHANGE THE FREQUENCY OF THE SIGNAL (IN SAME WORDS YOU CHANGE THE PERIOD TIME OF THE SIGNAL)
	*	***FOR PHASE CORRECT PWM***
	*	TAKE CARE OF THE FREQUENCY EQN 
	*	
	*	FOURTH THING==> YOU LOAD THE OCR1A VALUE TO DETERMINE THE DUTY CYCLE 
*/



/************************************************************************/
/*                        #INCLUDES                                    */
/************************************************************************/

#include "../DIO/DIO.h"
#include "../PWM/PWM_TIMER1.h"


/************************************************************************/
/*                        FUNCTIONS                                    */
/************************************************************************/






/**
 * brief: Initialize Timer1 in Fast PWM mode with configurable settings
 * note : This must be called before setting OCR1A/B or ICR1
 * param: prescaler Timer1 clock prescaler bits (e.g., (1<<CS11)|(1<<CS10))
 * param: outputMode COM1A/B bits for output behavior (non-inverting/inverting)
 * param: topValue   Value for ICR1 to define the PWM period
 */


void PWM_vInit_T1_Fast(PWM_Prescaler prescaler, PWM_FastModeType mode, PWM_OutputMode OC1A_mode, PWM_OutputMode OC1B_mode, u16 topValue)
{
	
	{
		TCNT1 = 0;

		switch (mode) {
			case FAST_EIGHT_BITS:
				TCCR1A = (1 << WGM10);
				TCCR1B = (1 << WGM12);
				break;
			case FAST_NINE_BITS:
				TCCR1A = (1 << WGM11);
				TCCR1B = (1 << WGM12);
				break;
			case FAST_TEN_BITS:
				TCCR1A = (1 << WGM11) | (1 << WGM10);
				TCCR1B = (1 << WGM12);
				break;
			case FAST_TOP_OCR1A:
				TCCR1A = (1 << WGM11);
				TCCR1B = (1 << WGM12) | (1 << WGM13);
				OCR1A = topValue;
				break;
			case FAST_TOP_ICR1:
				TCCR1A = (1 << WGM11);
				TCCR1B = (1 << WGM12) | (1 << WGM13);
				ICR1 = topValue;
				break;
		}

		// Set compare output modes
		TCCR1A |= (OC1A_mode << COM1A0) | (OC1B_mode << COM1B0);

		// Set prescaler last
		TCCR1B |= prescaler;
	}	
	
	
}



/**
 * brief: Initialize Timer1 in Phase Correct PWM mode with configurable settings
 * note : Use this if you want symmetric up-down counting waveform
 * param: prescaler Timer1 clock prescaler bits (e.g., (1<<CS11))
 * param: outputMode COM1A/B bits for output behavior (non-inverting/inverting)
 * param: topValue   Value for ICR1 to define the PWM period (top of counting)
 */
void PWM_vInit_T1_Phase(PWM_Prescaler prescaler, PWM_PhaseModeType mode, PWM_OutputMode OC1A_mode, PWM_OutputMode OC1B_mode, u16 topValue)
{
	TCNT1 = 0;

	switch (mode) {
		case PHASE_EIGHT_BITS:
		TCCR1A = (1 << WGM10);
		TCCR1B = 0;
		break;
		case PHASE_NINE_BITS:
		TCCR1A = (1 << WGM11);
		TCCR1B = 0;
		break;
		case PHASE_TEN_BITS:
		TCCR1A = (1 << WGM10) | (1 << WGM11);
		TCCR1B = 0;
		break;
		case PHASE_TOP_OCR1A:
		TCCR1A = (1 << WGM11);
		TCCR1B = (1 << WGM13);
		OCR1A = topValue;
		break;
		case PHASE_TOP_ICR1:
		TCCR1A = (1 << WGM11);
		TCCR1B = (1 << WGM13);
		ICR1 = topValue;
		break;
		case PHASE_FREQ_TOP_OCR1A:
		TCCR1A = 0;
		TCCR1B = (1 << WGM13);
		OCR1A = topValue;
		break;
		case PHASE_FREQ_TOP_ICR1:
		TCCR1A = 0;
		TCCR1B = (1 << WGM13);
		ICR1 = topValue;
		break;
	}

	// Set output modes
	TCCR1A |= (OC1A_mode << COM1A0) | (OC1B_mode << COM1B0);

	// Set prescaler last
	TCCR1B |= prescaler;
}




/**
 * brief: Set Output Compare Value for OC1A (Channel A)
 * param: copy_u16Value The compare match value to load into OCR1A
 */

void PWM_vSetValue_OCR1A_T1(u16 copy_u16Value)
{
	/*	WRITE_REG(OCR1A,copy_u16Value);	*/
	OCR1A = copy_u16Value ;
}



/**
 * brief: Set Output Compare Value for OC1B (Channel B)
 * param: copy_u16Value The compare match value to load into OCR1B
 */


void PWM_vSetValue_OCR1B_T1(u16 copy_u16Value)
{
	/*	WRITE_REG(OCR1B,copy_u16Value);	*/
	OCR1B = copy_u16Value ;
}




/**
 * brief: Set TOP value for Timer1 using ICR1 register
 * param: copy_u16Value The TOP value for PWM period control
 */


void PWM_vSetValue_ICR1_T1(u16 copy_u16Value)
{
	/*	WRITE_REG(ICR1,copy_u16Value);	*/
	ICR1 = copy_u16Value ;
}

