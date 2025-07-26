/*
 * Servo_Motor.c
 *
 * Created: 11/19/2024 11:22:51 PM
 *  Author: Zyad Ayman
 */

#include "Servo_Motor.h"
#include "../PWM/PWM_Timer1.h"
#include "../DIO/DIO.h"

/*
 * Function: SERVO_vInit
 * ---------------------
 * Initializes Timer1 in Fast PWM mode for controlling servo motors.
 */
void SERVO_vInit(u8 number_of_channels)
{
	if (number_of_channels == 1)
	{
		PWM_vInit_T1_Fast
		(
		PWM_PRESCALE_64,         // 8MHz / 64 = 125kHz timer clock
		FAST_TOP_ICR1,           // Fast PWM, TOP = ICR1
		PWM_NON_INVERTING,       // OC1A: Non-inverting mode
		PWM_DISCONNECTED,        // OC1B: not used for this servo
		2500                     // ICR1 = 2500 → 20ms period
		);
	} 
	else if(number_of_channels == 2)
	{
		PWM_vInit_T1_Fast
		(
		PWM_PRESCALE_64,         // 8MHz / 64 = 125kHz timer clock
		FAST_TOP_ICR1,           // Fast PWM, TOP = ICR1
		PWM_NON_INVERTING,       // OC1A: Non-inverting mode
		PWM_NON_INVERTING,        // OC1B: Non-inverting mode
		2500                     // ICR1 = 2500 → 20ms period
		);
	}
    
}

/*
 * Function: SERVO_vRotateMotor
 * ----------------------------
 * Rotates a servo motor connected to either OC1A or OC1B pin to a specific angle.
 *
 * Parameters:
 *   u8ChannelOutput - 'A' or 'B' to select OC1A or OC1B pin
 *   s8DegreesToRotate - Desired angle to rotate: supported values -90, -45, 0, +45, +90
 *
 * Notes:
 *   - For OC1A, PD5 is used.
 *   - For OC1B, PD4 is used.
 *   - PWM values are approximate based on a typical servo that responds to 1ms–2ms pulse widths.
 */
void SERVO_vRotateMotor(u8 u8ChannelOutput , s8 s8DegreesToRotate)
{
    if (u8ChannelOutput == 'A' || u8ChannelOutput == 'a')
    {
        /*	Channel OC1A	*/ 
        DIO_vSet_Pin_Direction('d', PIN_NO_5 , OUTPUT);

        switch (s8DegreesToRotate)
        {
			case SERVO_ANGLE_0:
					PWM_vSetValue_OCR1A_T1(125);   // ~1.0ms pulse
					break;

				case SERVO_ANGLE_45:
					PWM_vSetValue_OCR1A_T1(156);   // ~1.25ms pulse
					break;

				case SERVO_ANGLE_90:
					PWM_vSetValue_OCR1A_T1(187);   // ~1.5ms pulse
					break;

				case SERVO_ANGLE_135:
					PWM_vSetValue_OCR1A_T1(219);   // ~1.75ms pulse
					break;

				case SERVO_ANGLE_180:
					PWM_vSetValue_OCR1A_T1(250);   // ~2.0ms pulse
					break;
        }
    }
    else if (u8ChannelOutput == 'B' || u8ChannelOutput == 'b')
    {
        /*	Channel OC1B	*/ 
        DIO_vSet_Pin_Direction('d', PIN_NO_4 , OUTPUT);

        switch (s8DegreesToRotate)
        {
			case SERVO_ANGLE_0:
			PWM_vSetValue_OCR1B_T1(125);   // ~1.0ms pulse
			break;

			case SERVO_ANGLE_45:
			PWM_vSetValue_OCR1B_T1(156);   // ~1.25ms pulse
			break;

			case SERVO_ANGLE_90:
			PWM_vSetValue_OCR1B_T1(187);   // ~1.5ms pulse
			break;

			case SERVO_ANGLE_135:
			PWM_vSetValue_OCR1B_T1(219);   // ~1.75ms pulse
			break;

			case SERVO_ANGLE_180:
			PWM_vSetValue_OCR1B_T1(250);   // ~2.0ms pulse
			break;
        }
    }
}
