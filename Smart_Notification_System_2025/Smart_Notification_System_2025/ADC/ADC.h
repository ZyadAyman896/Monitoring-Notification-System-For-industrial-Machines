/*
 * ADC.h
 *
 * Created: 2/14/2024 9:55:08 PM
 *  Author: Zyad Ayman
 */ 


#ifndef ADC_H_
#define ADC_H_


#include "../HELPING FILES/std_types.h"

/************************************************************************/
/*                        ADC REGISTERS                                 */
/************************************************************************/



#define ADMUX *((volatile u8*)0x27)



#define ADCSRA *((volatile u8*)0x26)



#define ADCL *((volatile u8*)0x24)

#define ADCH *((volatile u8*)0x25)

#define ADC  *((volatile u16*)0x24)



#define SFIOR *((volatile u8*)0x50)

/************************************************************************/
/*                        ADC REGISTERS BITS                            */
/************************************************************************/


/* ADMUX bits */
#define REFS0   6   /** Reference Selection Bit 0 */
#define REFS1   7   /** Reference Selection Bit 1 */
#define ADLAR   5   /** ADC Left Adjust Result */

/* ADCSRA bits */
#define ADEN    7   /** ADC Enable */
#define ADSC    6   /** ADC Start Conversion */
#define ADATE   5   /** ADC Auto Trigger Enable */
#define ADIF    4   /** ADC Interrupt Flag */
#define ADIE    3   /** ADC Interrupt Enable */
#define ADPS2   2   /** ADC Prescaler Select Bit 2 */
#define ADPS1   1   /** ADC Prescaler Select Bit 1 */
#define ADPS0   0   /** ADC Prescaler Select Bit 0 */


/************************************************************************/
/*                        ADC CHANNELS                                 */
/************************************************************************/
#define ADC_CHANNEL_0       (0) 
#define ADC_CHANNEL_1       (1)
#define ADC_CHANNEL_2       (2)
#define ADC_CHANNEL_3       (3)
#define ADC_CHANNEL_4       (4) 
#define ADC_CHANNEL_5       (5)
#define ADC_CHANNEL_6       (6)
#define ADC_CHANNEL_7       (7) 


/************************************************************************/
/*                        FUNCTIONS LIKE MACROS                         */
/************************************************************************/

/*   */
#define ADC_vStart_Conv() ( SET_PIN( ADCSRA , PIN_NO_6 ) )


/************************************************************************/
/*                        FUNCTIONS PROTOTYPES                          */
/************************************************************************/



/**
 * brief: Initializes the ADC peripheral with AVCC as reference and prescaler of 128.
 * 
 * This sets the ADC reference voltage to AVCC (typically 5V),
 * enables the ADC, and configures it to run at 62.5 kHz (for 8 MHz F_CPU).
 * Channel selection is done later in the read function.
 * 
 */

void ADC_vInit(void);


/**
 * brief : Reads the ADC value from a specified channel.
 * 
 * param : channel The ADC channel number (0 to 7) to read from.
 * 
 * return : u16 The 10-bit digital result from the selected ADC channel.
 * 
 * This function selects the ADC input channel, starts a conversion,
 * waits for it to complete, then returns the result.
 */

u16 ADC_u16Read_Value(u8 ADC_Channel);




#endif /* ADC_H_ */