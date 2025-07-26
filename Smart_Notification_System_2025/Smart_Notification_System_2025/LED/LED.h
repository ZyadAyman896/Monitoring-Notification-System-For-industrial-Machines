/*
 * LED.h
 *
 * Created: 11/3/2023 1:36:34 PM
 *  Author: Zyad Ayman
 */ 


#ifndef LED_H_
#define LED_H_
#include "../DIO/DIO.h"
#include "../Helping Files/std_types.h"

void LED_vTurnOffLED(u8 copy_PORT_NAME,u8 copy_PIN_NUMBER);
void LED_vTurnOnLED(u8 copy_PORT_NAME,u8 copy_PIN_NUMBER);
void LED_vToggle_Led(u8 copy_PORT_NAME,u8 copy_PIN_NUMBER);
void LED_vBlink_Led(u8 copy_PORT_NAME , u8 copy_PIN_NUMBER);
void LED_vTurnOn_Multiple_Leds(u8 copy_PORT_NAME , u8 copy_NUMBER_OF_LEDS);
void LED_vTurnOff_Multiple_Leds(u8 copy_PORT_NAME , u8 copy_NUMBER_OF_LEDS);
#endif /* LED_H_ */