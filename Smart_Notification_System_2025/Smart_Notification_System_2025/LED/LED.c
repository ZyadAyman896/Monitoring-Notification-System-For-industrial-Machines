/*
 * LED.c
 *
 * Created: 11/3/2023 1:36:55 PM
 *  Author: Zyad Ayman
 */ 
#define F_CPU 8000000UL
#include "../DIO/DIO.h"
#include <util/delay.h>


void LED_vTurnOnLED(u8 copy_PORT_NAME,u8 copy_PIN_NUMBER)
{
	
	DIO_vSet_Pin_Direction(copy_PORT_NAME,copy_PIN_NUMBER,OUTPUT);
	DIO_vSet_Pin_Value(copy_PORT_NAME,copy_PIN_NUMBER,LED_ON);
	
}
void LED_vTurnOffLED(u8 copy_PORT_NAME,u8 copy_PIN_NUMBER)
{
	
	DIO_vSet_Pin_Direction(copy_PORT_NAME,copy_PIN_NUMBER,OUTPUT);
	DIO_vSet_Pin_Value(copy_PORT_NAME,copy_PIN_NUMBER,LED_OFF);
	
}

void LED_vToggle_Led(u8 copy_PORT_NAME,u8 copy_PIN_NUMBER)
{
	DIO_vToggle_Pin_Value(copy_PORT_NAME,copy_PIN_NUMBER);
	
}
//this function blinks the led for 3 iterations with delay of half second 
void LED_vBlink_Led(u8 copy_PORT_NAME , u8 copy_PIN_NUMBER)
{
	for (int i = 0 ; i < 3 ; i++ )
	{
			LED_vTurnOnLED(copy_PORT_NAME,copy_PIN_NUMBER);
			_delay_ms(300);
			LED_vTurnOffLED(copy_PORT_NAME,copy_PIN_NUMBER);
			_delay_ms(300);
	}

}
//we use it when we want to turn on multiple leds 
//first this functions sets the ddrs to be output 
//second it outputs 1 to number of leds you have passed it 
void LED_vTurnOn_Multiple_Leds(u8 copy_PORT_NAME , u8 copy_NUMBER_OF_LEDS)
{
		switch (copy_NUMBER_OF_LEDS)
		{
			case 1:
					DIO_vSet_Port_Direction(copy_PORT_NAME,0x01);
					DIO_vSet_Port_Value(copy_PORT_NAME,0x01);
			break;
			case 2:
					DIO_vSet_Port_Direction(copy_PORT_NAME ,0x03 );
					DIO_vSet_Port_Value(copy_PORT_NAME,0x03);
			break;
			case 3:
					DIO_vSet_Port_Direction(copy_PORT_NAME , 0x07);
					DIO_vSet_Port_Value(copy_PORT_NAME,0x07);
			break;
			case 4:
					DIO_vSet_Port_Direction(copy_PORT_NAME , 0x0f);
					DIO_vSet_Port_Value(copy_PORT_NAME,0x0f);
			break;
			case 5:
					DIO_vSet_Port_Direction(copy_PORT_NAME ,0x1f );
					DIO_vSet_Port_Value(copy_PORT_NAME,0x1f);
			break;
			case 6:
					DIO_vSet_Port_Direction(copy_PORT_NAME ,0x3f );
					DIO_vSet_Port_Value(copy_PORT_NAME,0x3f);
			break;
			case 7:
					DIO_vSet_Port_Direction(copy_PORT_NAME ,0x7f );
					DIO_vSet_Port_Value(copy_PORT_NAME,0x7f);
			break;
			case 8:
					DIO_vSet_Port_Direction(copy_PORT_NAME , 0xff);
					DIO_vSet_Port_Value(copy_PORT_NAME,0xff);
			break;
		}

}



void LED_vTurnOff_Multiple_Leds(u8 copy_PORT_NAME , u8 copy_NUMBER_OF_LEDS)
{
	switch (copy_NUMBER_OF_LEDS)
	{
		case 1:
		DIO_vSet_Port_Direction(copy_PORT_NAME,0x7f);
		DIO_vSet_Port_Value(copy_PORT_NAME,0x7f);
		break;
		case 2:
		DIO_vSet_Port_Direction(copy_PORT_NAME ,0x3f );
		DIO_vSet_Port_Value(copy_PORT_NAME,0x3f);
		break;
		case 3:
		DIO_vSet_Port_Direction(copy_PORT_NAME , 0x1f);
		DIO_vSet_Port_Value(copy_PORT_NAME,0x1f);
		break;
		case 4:
		DIO_vSet_Port_Direction(copy_PORT_NAME , 0x0f);
		DIO_vSet_Port_Value(copy_PORT_NAME,0x0f);
		break;
		case 5:
		DIO_vSet_Port_Direction(copy_PORT_NAME ,0x07 );
		DIO_vSet_Port_Value(copy_PORT_NAME,0x07);
		break;
		case 6:
		DIO_vSet_Port_Direction(copy_PORT_NAME ,0x03 );
		DIO_vSet_Port_Value(copy_PORT_NAME,0x03);
		break;
		case 7:
		DIO_vSet_Port_Direction(copy_PORT_NAME ,0x01 );
		DIO_vSet_Port_Value(copy_PORT_NAME,0x01);
		break;
		case 8:
		DIO_vSet_Port_Direction(copy_PORT_NAME , 0x00);
		DIO_vSet_Port_Value(copy_PORT_NAME,0x00);
		break;
	}
	
}