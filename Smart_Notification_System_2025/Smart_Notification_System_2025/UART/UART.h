#ifndef UART_H_
#define UART_H_

#include "../Helping Files/std_types.h"

/************************************************************************/
/*                        CONFIGURATIONS                                */
/************************************************************************/

typedef enum {
	UART_INTERRUPT_DISABLE,
	UART_INTERRUPT_ENABLE
} UART_InterruptMode;

typedef enum {
	UART_BAUD_9600   ,
	UART_BAUD_38400  ,
	UART_BAUD_115200 
} UART_BaudRate;

/************************************************************************/
/*                        UART REGISTERS                                */
/************************************************************************/

#define UDR   *((volatile u8 *)0x2C)
#define UCSRA *((volatile u8 *)0x2B)
#define UCSRB *((volatile u8 *)0x2A)
#define USCRC *((volatile u8 *)0x40)
#define UBRRL *((volatile u8 *)0x29)
#define UBRRH *((volatile u8 *)0x40)

/************************************************************************/
/*                        Function Prototypes                           */
/************************************************************************/

void UART_vInit(UART_InterruptMode mode, UART_BaudRate baud);
void UART_vSendData(u8 copy_u8Data);
u8 UART_u8GetData(void);
void UART_vSendString(Pu8 Ptr);

/* Flow control */
void UART_vEnable_Flow_Control(void);
void UART_vDisable_Flow_Control(void);

/* Callback setters */
void UART_vSetRxCallback(void (*callback)(u8));
void UART_vSetTxCallback(void (*callback)(void));

#endif /* UART_H_ */
