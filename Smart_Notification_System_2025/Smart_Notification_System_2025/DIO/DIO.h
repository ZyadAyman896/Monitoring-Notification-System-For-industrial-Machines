/*
 * DIO.h
 *
 * Created: 11/3/2023 11:49:36 AM
 *  Author: Zyad Ayman
 */ 

#ifndef DIO_H_
#define DIO_H_

#include "../Helping Files/std_types.h"
#include "../Helping Files/Utils.h"


/*	DIO Registers	*/

#define PORTA *((volatile char *)0x3B)
#define PINA *((volatile char *)0x39)
#define DDRA *((volatile char *)0x3A)
#define PORTB *((volatile char *)0x38)
#define PINB *((volatile char *)0x36)
#define DDRB *((volatile char *)0x37)
#define PORTC *((volatile char *)0x35)
#define PINC *((volatile char *)0x33)
#define DDRC *((volatile char *)0x34)
#define PORTD *((volatile char *)0x32)
#define PIND *((volatile char *)0x30)
#define DDRD *((volatile char *)0x31)



void DIO_vSet_Port_Direction(u8 copy_u8PortName ,u8 copy_u8PortDirection);
void DIO_vSet_Pin_Value(u8 copy_u8PortName , u8 copy_u8PinNumber ,u8 copy_u8PinValue);
void DIO_vSet_Pin_Direction(u8 copy_u8PortName , u8 copy_u8PinNumber ,u8 copy_u8PinDirection);
void DIO_vSet_Port_Value(u8 copy_u8PortName ,u8 copy_u8PortValue);
void DIO_vToggle_Port_Value(u8 copy_u8PortName);
void DIO_vToggle_Pin_Value(u8 copy_u8PortName, u8 copy_u8PinNumber);
u8 DIO_u8GET_Pin_value(u8 copy_u8PinName,u8 copy_u8PinNumber);
u8 DIO_u8GET_Port_value(u8 copy_u8PinName );



#endif /* DIO_H_ */