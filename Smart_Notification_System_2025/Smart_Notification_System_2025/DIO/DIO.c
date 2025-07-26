/*
 * DIO.c
 *
 * Created: 11/3/2023 12:53:18 PM
 *  Author: Zyad Ayman
 */ 
#include "DIO.h"
//SETS PIN PIN  , DDR'S
void DIO_vSet_Pin_Direction(u8 copy_u8PortName , u8 copy_u8PinNumber ,u8 copy_u8PinDirection)
{
	switch (copy_u8PortName)
	{
		case'A':
		case 'a':
			if(copy_u8PinDirection == OUTPUT)
				SET_PIN(DDRA,copy_u8PinNumber);
			else
				CLR_PIN(DDRA,copy_u8PinNumber);
		//WRITE_BIT(DDRA,copy_u8PinNumber,copy_u8PinDirection);
		break;
		case'B':
		case 'b':
			if(copy_u8PinDirection == OUTPUT)
				SET_PIN(DDRB,copy_u8PinNumber);
			else
				CLR_PIN(DDRB,copy_u8PinNumber);
		break;
		case'C':
		case 'c':
			if(copy_u8PinDirection == OUTPUT)
				SET_PIN(DDRC,copy_u8PinNumber);
			else
				CLR_PIN(DDRC,copy_u8PinNumber);
		break;
		case'D':
		case 'd':
			if(copy_u8PinDirection == OUTPUT)
				SET_PIN(DDRD,copy_u8PinNumber);
			else
				CLR_PIN(DDRD,copy_u8PinNumber);
		break;
		
		
	}
}

//SETS or clear PIN PIN , PORT'S
void DIO_vSet_Pin_Value(u8 copy_u8PortName , u8 copy_u8PinNumber ,u8 copy_u8PinValue)
{
	switch (copy_u8PortName)
	{
		case'A':
		case 'a':
			if(copy_u8PinValue == ZERO)
				CLR_PIN(PORTA,copy_u8PinNumber);
			else
				SET_PIN(PORTA,copy_u8PinNumber);
		//WRITE_BIT(PORTA,copy_u8PinNumber,copy_u8PinValue);
		break;
		case'B':
		case 'b':
			if(copy_u8PinValue == ZERO)
				CLR_PIN(PORTB,copy_u8PinNumber);
			else
				SET_PIN(PORTB,copy_u8PinNumber);
		break;
		case'C':
		case 'c':
			if(copy_u8PinValue == ZERO)
				CLR_PIN(PORTC,copy_u8PinNumber);
			else
				SET_PIN(PORTC,copy_u8PinNumber);
		break;
		case'D':
		case 'd':
			if(copy_u8PinValue == ZERO)
				CLR_PIN(PORTD,copy_u8PinNumber);
			else
				SET_PIN(PORTD,copy_u8PinNumber);
		break;
	}
}

//SETS THE WHOLE  REGISTER VALUE , DDR's
void DIO_vSet_Port_Direction(u8 copy_u8PortName ,u8 copy_u8PortDirection)
{
	switch (copy_u8PortName)
	{
		case'A':
		case 'a':
		WRITE_REG(DDRA,copy_u8PortDirection);
		break;
		case'B':
		case 'b':
		WRITE_REG(DDRB,copy_u8PortDirection);
		break;
		case'C':
		case 'c':
		WRITE_REG(DDRC,copy_u8PortDirection);
		break;
		case'D':
		case 'd':
		WRITE_REG(DDRD,copy_u8PortDirection);
		break;
	}
}

//SETS THE WHOLE REGISTER , PORT'S

void DIO_vSet_Port_Value(u8 copy_u8PortName ,u8 copy_u8PortValue)
{
	switch (copy_u8PortName)
	{
		case'A':
		case 'a':
		WRITE_REG(PORTA,copy_u8PortValue);
		break;
		case'B':
		case 'b':
		WRITE_REG(PORTB,copy_u8PortValue);
		break;
		case'C':
		case 'c':
		WRITE_REG(PORTC,copy_u8PortValue);
		break;
		case'D':
		case 'd':
		WRITE_REG(PORTD,copy_u8PortValue);
		break;
	}
}

//GETS PIN PIN , INPUT PIN's
u8 DIO_u8GET_Pin_value(u8 copy_u8PinName,u8 copy_u8PinNumber)
{
		switch (copy_u8PinName)
		{
			case'A':
			case 'a':
			return READ_PIN(PINA,copy_u8PinNumber);
			break;
			case'B':
			case 'b':
			return READ_PIN(PINB,copy_u8PinNumber);
			break;
			case'C':
			case 'c':
			return READ_PIN(PINC,copy_u8PinNumber);
			break;
			case'D':
			case 'd':
			return READ_PIN(PIND,copy_u8PinNumber);
			break;
		}
}

//GETS THE WHOLE REGISTER VALUE , INPUT PIN'S
u8 DIO_u8GET_Port_value(u8 copy_u8PinName )
{
		switch (copy_u8PinName)
		{
			case'A':
			case 'a':
			return READ_WHOLE_REG(PINA);
			break;
			case'B':
			case 'b':
			return READ_WHOLE_REG(PINB);
			break;
			case'C':
			case 'c':
			return READ_WHOLE_REG(PINC);
			break;
			case'D':
			case 'd':
			return READ_WHOLE_REG(PIND);
			break;
		}
}
//TOGGLE PIN VALUE
void DIO_vToggle_Pin_Value(u8 copy_u8PortName, u8 copy_u8PinNumber)
{
	
	switch(copy_u8PortName)
	{
		case'A':
		case 'a':
		TOGGLE_BIT(PORTA,copy_u8PinNumber);
		break;
		case'B':
		case 'b':
		TOGGLE_BIT(PORTB,copy_u8PinNumber);
		break;
		case'C':
		case 'c':
		TOGGLE_BIT(PORTC,copy_u8PinNumber);
		break;
		case'D':
		case 'd':
		TOGGLE_BIT(PORTD,copy_u8PinNumber);
		break;
	}
	
	
}
//TOGGLE PORT VALUE
void DIO_vToggle_Port_Value(u8 copy_u8PortName)
{
	
	switch(copy_u8PortName)
	{
		case'A':
		case 'a':
		TOGGLE_REG(PORTA);
		break;
		case'B':
		case 'b':
		TOGGLE_REG(PORTB);
		break;
		case'C':
		case 'c':
		TOGGLE_REG(PORTC);
		break;
		case'D':
		case 'd':
		TOGGLE_REG(PORTD);
		break;
	}
	
	
}