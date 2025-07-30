#ifndef ADC_H_
#define ADC_H_

#include "../HELPING FILES/std_types.h"
#include "../HELPING FILES/Utils.h"

/************************************************************************/
/*                        ADC REGISTERS                                 */
/************************************************************************/
#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCL    *((volatile u8*)0x24)
#define ADCH    *((volatile u8*)0x25)
#define ADC     *((volatile u16*)0x24)
#define SFIOR   *((volatile u8*)0x50)

/************************************************************************/
/*                        ADC REGISTERS BITS                            */
/************************************************************************/
#define REFS0   6
#define REFS1   7
#define ADLAR   5
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

/************************************************************************/
/*                        ADC CONFIG ENUMS                              */
/************************************************************************/
typedef enum {
	ADC_REF_AREF = 0,
	ADC_REF_AVCC = 1,
	ADC_REF_INTERNAL = 3
} ADC_Reference_t;

typedef enum {
	ADC_RIGHT_ADJUST = 0,
	ADC_LEFT_ADJUST = 1
} ADC_Adjust_t;

typedef enum {
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128
} ADC_Prescaler_t;

/************************************************************************/
/*                        ADC CONFIG STRUCT                             */
/************************************************************************/
typedef struct {
	ADC_Reference_t ref;
	ADC_Adjust_t adjust;
	ADC_Prescaler_t prescaler;
	u8 auto_trigger;      /*	0 or 1	*/ 
	u8 interrupt_enable;  /*	0 or 1 ? enable ADC interrupt	*/ 
} ADC_Config_t;

/************************************************************************/
/*                        ADC CHANNELS                                  */
/************************************************************************/
#define ADC_CHANNEL_0       0
#define ADC_CHANNEL_1       1
#define ADC_CHANNEL_2       2
#define ADC_CHANNEL_3       3
#define ADC_CHANNEL_4       4
#define ADC_CHANNEL_5       5
#define ADC_CHANNEL_6       6
#define ADC_CHANNEL_7       7

/************************************************************************/
/*                        FUNCTION MACROS & PROTOTYPES                  */
/************************************************************************/
#define ADC_vStart_Conv()   SET_PIN(ADCSRA, ADSC)

void ADC_vInit(const ADC_Config_t* config);
u16  ADC_u16Read_Value(u8 ADC_Channel);

void ADC_SetCallback(void (*callback)(u16));


#endif /* ADC_H_ */
