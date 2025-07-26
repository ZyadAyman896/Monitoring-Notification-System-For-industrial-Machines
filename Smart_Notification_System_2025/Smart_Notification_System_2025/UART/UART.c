/*
 * UART.c
 *
 * Created: 3/6/2024 9:38:53 PM
 *  Author: Zyad Ayman
 */ 
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "../DIO/DIO.h"
#include "../Helping Files/Utils.h"

/**/
static void (*UART_RX_Callback)(u8) = NULL;
static void (*UART_TX_Callback)(void) = NULL;


void UART_vInit(UART_InterruptMode mode, UART_BaudRate baud)
{
	/* Enable Tx & Rx */
	UCSRB = (1 << 4) | (1 << 3);  /*	RXEN, TXEN	*/ 

	/* Even parity, 1 stop bit, 8-bit data */
	USCRC = 0xA6;

	/*	Set baud rate based on the selected enum	*/ 
    if (baud == UART_BAUD_9600)
    {
	    UBRRL = 51;
	    UBRRH = 0;
    }
    else if (baud == UART_BAUD_38400)
    {
	    UBRRL = 12;
	    UBRRH = 0;
    }
    else if (baud == UART_BAUD_115200)
    {
	    UBRRL = 3;
	    UBRRH = 0;
    }



	if (mode == UART_INTERRUPT_ENABLE) 
	{
		UCSRB |= (1 << 7) | (1 << 6); /*	RXCIE, TXCIE	*/ 
	}
	
}


void UART_vSendData( u8 copy_u8Data )
{
	while( READ_PIN( UCSRA , PIN_NO_5 ) == 0 );

	UDR = copy_u8Data ;
	
}


u8 UART_u8GetData(void)
{

	while(READ_PIN(UCSRA,PIN_NO_7) == 0);

	return READ_WHOLE_REG(UDR);
}


void UART_vSendString( Pu8 Ptr )
{
	while( *Ptr != '\0' )
	{
		UART_vSendData( *Ptr ) ;
		
		Ptr++ ;
	}

}

/*	Those Functions to make handshaking algorithm */

/*	Function to enable UART flow control	*/ 

void UART_vEnable_Flow_Control() {

	/*	Configure RTS and CTS pins as outputs/inputs	*/ 
	/*	CTS pin as input	*/

	DIO_vSet_Pin_Direction('d',PIN_NO_2,INPUT);
	
	/*	RTS pin as output	*/ 
	DIO_vSet_Pin_Direction('d',PIN_NO_3,OUTPUT);

}

/*	Function to disable UART flow control 	*/ 
void UART_vDisable_Flow_Control() {
	// Restore RTS pin as input (disable flow control)
	DIO_vSet_Pin_Direction('d',PIN_NO_3,INPUT);
}

/************************************************************************/
/*						Callback Setters							    */
/************************************************************************/

/* Set RX callback */
void UART_vSetRxCallback(void (*callback)(u8))
{
	UART_RX_Callback = callback;
}

/* Set TX callback */
void UART_vSetTxCallback(void (*callback)(void))
{
	UART_TX_Callback = callback;
}

/************************************************************************/
/*								ISRS									*/
/************************************************************************/

/*	RX Complete Interrupt	*/ 
ISR(USART_RXC_vect)
{
	
	if (UART_RX_Callback != NULL) 
	{
		UART_RX_Callback(UDR); /*	Pass received byte	*/ 
	}
	
}

/*	TX Complete Interrupt	*/ 
ISR(USART_TXC_vect)
{
	
	if (UART_TX_Callback != NULL) 
	{
		UART_TX_Callback();
	}
	
}