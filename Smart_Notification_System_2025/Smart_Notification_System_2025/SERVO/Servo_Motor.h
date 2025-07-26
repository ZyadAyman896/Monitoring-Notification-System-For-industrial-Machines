/*
 * Servo_Motor.h
 *
 * Created: 11/19/2024 11:23:08 PM
 *  Author: Zyad Ayman
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_


#include "../Helping Files/std_types.h"
#include "../Helping Files/Utils.h"

/************************************************************************/
/*					Configurations                                      */
/************************************************************************/
typedef enum 
{
	SERVO_ANGLE_0   ,   
	SERVO_ANGLE_45  ,   
	SERVO_ANGLE_90  ,     
	SERVO_ANGLE_135      ,
	SERVO_ANGLE_180		 ,
	SERVO_ANGLE_MINUS_45 ,
	SERVO_ANGLE_MINUS_90 ,
  
} ServoAngle;

/************************************************************************/
/*					Functions Prototypes                                */
/************************************************************************/
void SERVO_vInit(u8 number_of_channels);
void SERVO_vRotateMotor(u8 u8ChannelOutput , s8 s8DegreesToRotate);




#endif /* SERVO_MOTOR_H_ */