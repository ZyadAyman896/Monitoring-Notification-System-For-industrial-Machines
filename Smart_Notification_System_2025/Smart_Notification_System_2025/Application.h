/*
 * Application.h
 *
 * Created: 7/26/2025 8:15:59 PM
 *  Author: Zyad Ayman
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

/************************************************************************/
/*							#INCLUDES                                   */
/************************************************************************/
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC/ADC.h"
#include "DIO/DIO.h"
#include "LCD/LCD.h"
#include "LED/LED.h"
#include "HELPING FILES/std_types.h"
#include "HELPING FILES/Utils.h"
#include "ICU/ICU.h"
#include "EXTI/EXTI.h"
#include "TIMERS/Timers.h"
#include "PWM/PWM_Timer1.h"
#include "SERVO/Servo_Motor.h"
#include "UART/UART.h"

/************************************************************************/
/*						#defines for used Macros                        */
/************************************************************************/

#define DISTANCE_THRESHOLD_CM 0.5
#define CRITICAL_DISTANCE_CM  200


/************************************************************************/
/*                        Functions Prototypes                          */
/************************************************************************/

/*	Function Prototype for Callback		*/
void CTC_TimerHandler(void);

/*	Interrupt Handler */
void EXTI0_Handler(void);

/*	Interrupt Handler */
void EXTI1_Handler(void);

/*	Function That sends the trigger pulse for the ultrasonic distance	*/
void Send_Trigger_Pulse(void);

/*	Callback function that will be called in the ISR	*/
void ICU_Handler(void);

/**/
void UART_RX_Handler(u8 DataReceived);



#endif /* APPLICATION_H_ */