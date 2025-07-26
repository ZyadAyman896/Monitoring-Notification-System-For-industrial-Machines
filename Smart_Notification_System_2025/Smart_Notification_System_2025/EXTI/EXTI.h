/*
 * EXTI.h
 *
 * Created: 7/22/2025 7:57:53 PM
 *  Author: Zyad Ayman
 */ 


#ifndef EXTI_H_
#define EXTI_H_

#include "../Helping Files/std_types.h"


/************************************************************************/
/*                        Configurations                                */
/************************************************************************/

typedef enum
{
	/* For INT0 and INT1	*/
	EXTI_LOW_LEVEL,
	EXTI_ANY_CHANGE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE

} EXTI_SenseMode;



typedef enum
{
	
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2
	
}EXTI_InterruptNumber;

/************************************************************************/
/*                   Register Definitions & Bits                        */
/************************************************************************/


/* MCU Control Register (INT0, INT1 sense control) */
#define MCUCR   (*(volatile u8*)0x55)

/* MCU Control and Status Register (INT2 sense control) */
#define MCUCSR  (*(volatile u8*)0x54)

/* General Interrupt Control Register (INTx enable) */
#define GICR    (*(volatile u8*)0x5B)

/* General Interrupt Flag Register (INTx flags) */
#define GIFR    (*(volatile u8*)0x5A)

/* ---------------------- Bit Definitions ---------------------- */

/* MCUCR bits for INT0 */
#define ISC00   0
#define ISC01   1

/* MCUCR bits for INT1 */
#define ISC10   2
#define ISC11   3

/* MCUCSR bit for INT2 */
#define ISC2    6

/* GICR bits for enabling INTx */
#define INT0_EN_BIT   6
#define INT1_EN_BIT   7
#define INT2_EN_BIT   5

/* GIFR bits for flags (optional use) */
#define INTF0_FLAG    6
#define INTF1_FLAG    7
#define INTF2_FLAG    5



/****************************************Registers for DIO used PINS****************************************/

/* ------------- PORTB Registers ------------- */
#define PORTB   (*(volatile u8*)0x38)
#define DDRB    (*(volatile u8*)0x37)
#define PINB    (*(volatile u8*)0x36)

/* ------------- PORTD Registers ------------- */
#define PORTD   (*(volatile u8*)0x32)
#define DDRD    (*(volatile u8*)0x31)
#define PIND    (*(volatile u8*)0x30)



/************************************************************************/
/*                        Functions Prototypes                          */
/************************************************************************/


/**
 * @brief Initialize the specified external interrupt with trigger mode
 * 
 * @param int_num: EXTI_INT0, EXTI_INT1, or EXTI_INT2
 * @param sense_mode: One of the defined sense control modes
 */
void EXTI_vInit(u8 interrupt_number, EXTI_SenseMode sense_mode);

/**
 * @brief Enable the specified external interrupt
 * 
 * @param int_num: EXTI_INT0, EXTI_INT1, or EXTI_INT2
 */
void EXTI_vEnable(u8 interrupt_number);

/**
 * @brief Disable the specified external interrupt
 * 
 * @param int_num: EXTI_INT0, EXTI_INT1, or EXTI_INT2
 */
void EXTI_vDisable(u8 interrupt_number);

/**
 * @brief Register a callback function for the specified interrupt
 * 
 * @param int_num: EXTI_INT0, EXTI_INT1, or EXTI_INT2
 * @param callback: Pointer to user function (void func(void))
 */
void EXTI_vSetCallback(u8 interrupt_number, void (*callback)(void));



#endif /* EXTI_H_ */