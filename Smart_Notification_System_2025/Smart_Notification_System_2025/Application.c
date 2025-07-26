/*
 * Smart_Notification_System_2025.c
 *
 * Created: 7/26/2025 4:20:23 AM
 * Author : Zyad Ayman
 */ 


/*	CPU Speed	*/
#define F_CPU 8000000UL

#include "Application.h"


/************************************************************************/
/*                        global Variables			                    */
/************************************************************************/

u8 DataReceived ;

volatile u8  g_state = 0 ;
volatile u16 g_start_time = 0;
volatile u16 g_end_time = 0;
volatile u16 g_pulse_width = 0;
volatile float32 g_distance_cm = 0;
volatile float32 g_last_distance = -1;  /* Initialized to an impossible value	*/


/**/
volatile u8 g_smoke_flag = 0;

/**/
volatile u8 g_vibration_flag = 0;

/**/
volatile u8 g_Usage_Time_ofMachine_flag = 0;




/************************************************************************/
/*                           Main code                                  */
/************************************************************************/


int main(void)
{
	
	
		/*	Variable for data received for UART		*/
		u8 DataReceived ;
		
		
		/*	Init of the Servo motor		*/
		SERVO_vInit(2);	
		
		/*	LCD Init	*/
		LCD_vInit();
	
	
		/*****************************************************************************/
		/*****************************Timers Config***********************************/	
	
		/*	Configuring  Timer1	for CTC Mode with interrupt 	*/
		Timer1_Configurations config =
		{
			.Mode = TIMER1_MODE_CTC ,	/*	Normal Overflow Mode	*/
			.Interrupt_timer1 = TIMER1_INTERRUPT_ENABLED	/*	Interrupt Enabled	*/
	    
		};

		/*****************************************************************************/
		/*****************************Ultrasonic Init*********************************/
	
		/*	Init of ICU		*/
		ICU_Init(ICU_RISING_EDGE);

		/*	Setting Trigger Pin as OUTPUT ==>> PD0	*/
		DIO_vSet_Pin_Direction('c',PIN_NO_0 ,OUTPUT);

		/*	Setting Up the Callback funtion		*/
		ICU_SetCallback(ICU_Handler);
	
		/*****************************************************************************/

		/*****************************************************************************/
		/*******************************TIMER Init************************************/
    
		/*	Initialization of Timer1	*/
		TIMER1_vInit(&config);
    
		/*	putting the value to get 1 sec	*/
		TIMER1_vSetValueCompareCTC(7813);
        
		/*	Setting Callback for timer ISR	*/
		TIMER1_vSetCompareCTCCallback(CTC_TimerHandler);
    
		/*	Prescaler Value	= 1024	*/
		TIMER1_vStart(TIMER1_PRESCALER_1024);
    
		/*****************************************************************************/
		/*******************************EXTI******************************************/	
	
		/*	Initializing External Interrupt 0	*/
		EXTI_vInit(EXTI_INT0,EXTI_FALLING_EDGE);

		/*	Initializing External Interrupt 0	*/
		EXTI_vInit(EXTI_INT1,EXTI_FALLING_EDGE);
	
		/*	Enabling EXTI0	*/
		EXTI_vEnable(EXTI_INT0);
	
		/*	Enabling EXTI0	*/
		EXTI_vEnable(EXTI_INT1);
	
		/*	Setting Callback Function to be executed by the ISR of INTERRUPT0	*/
		EXTI_vSetCallback(EXTI_INT0,EXTI0_Handler);
	
		/*	Setting Callback Function to be executed by the ISR of INTERRUPT0	*/
		EXTI_vSetCallback(EXTI_INT1,EXTI1_Handler);		
		
		/************************************************************************/
		/*                          UART INIT                                   */
		/************************************************************************/
		
		/*	Initiallizing UART for using Bluetooth */
		UART_vInit(UART_INTERRUPT_ENABLE,UART_BAUD_9600);
	
		/*	Setting the callback function to be called by the ISR	*/
		UART_vSetRxCallback(UART_RX_Handler);    
	
	
		/*	Enable Global Interrupt		*/
		sei();
    
		/*****************************************************************************/
	
		_delay_ms(10);
	
		/*	Clear Display	*/
		LCD_vClear_Display();		
    
    while (1) 
    {
		
		/*	Checking on activation of Much Time usage of machine Flag from the ISR or not	*/
		if (g_Usage_Time_ofMachine_flag == 1)
		{
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();
						
			/*	Alerting for Much Time usage of machine on LCD	*/
			LCD_vBlinkCenteredStrings("Turn-Off","The Machine",3);

			/*	flag deactivation	*/
			g_Usage_Time_ofMachine_flag = 0;
			
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();			
		}
		
		/*	Checking on activation of High Vibration Flag from the ISR or not	*/
		if (g_vibration_flag == 1) 
		{
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();
			
			/*	Alerting for High vibration detecting on LCD	*/
			LCD_vBlinkCenteredStrings("High", "Vibration", 3);
			
			/*	flag deactivation	*/
			g_vibration_flag = 0;

			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();			
		}
		
		/*	Checking on activation of Smoke Detection Flag from the ISR or not	*/
		if (g_smoke_flag == 1) 
		{
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();
			
			/*	Alerting for Smoke detecting on LCD	*/
			LCD_vBlinkCenteredStrings("Smoke", "Detected", 3);
			
			/*	flag deactivation	*/
			g_smoke_flag = 0;

			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();			
		}


		/* Send Trigger to Ultrasonic */
	    Send_Trigger_Pulse();
		/*	Delay for ultrasonic also	*/
	    _delay_ms(30);
		
		

		if (fabs(g_distance_cm - g_last_distance) >= DISTANCE_THRESHOLD_CM)
		{
			
			LCD_vSendString_xy(0,0,"Distance=      ");  /*	Pad with spaces to clear old values	*/ 

			/*	Move to position after "Distance="	*/ 
			LCD_vMoveCursor(0, 9);
			LCD_vSendFloat(g_distance_cm, 1);    /*	Print with 1 decimal place	*/ 

			
			LCD_vSendString_xy(1,0,"cm          ");     /*	Clear any old unit or data	*/ 

			/*	Updating the value of the distance	*/
			g_last_distance = g_distance_cm;
		}

		/*	Even if the distance hasn’t changed, still check if it’s too close	*/ 
		if (g_distance_cm <= CRITICAL_DISTANCE_CM)
		{
			/*	Turn on The responsible LED	*/
			LED_vTurnOnLED('a', PIN_NO_0);
		}
		else if(g_distance_cm > CRITICAL_DISTANCE_CM)
		{
			/*	Turn off The responsible LED	*/
			LED_vTurnOffLED('a', PIN_NO_0);
		}


	    _delay_ms(200);		
		
    
	
	
	}
	
	
	
}


/************************************************************************/
/*								ISR										*/
/************************************************************************/

/**/
void CTC_TimerHandler()
{
	static u8 counter = 0 ;
	
	if(counter >= 30)
	{

		/**/
		g_Usage_Time_ofMachine_flag = 1 ;
		
		/**/
		counter = 0 ;
	}
	
	counter++;
	
	
}



/**/
void EXTI0_Handler()
{

	
	 g_vibration_flag = 1;
}





/**/
void EXTI1_Handler(void)
{

	g_smoke_flag = 1 ;
	
}



/*	Function That sends the trigger pulse for the ultrasonic distance	*/
void Send_Trigger_Pulse(void) 
{
	DIO_vSet_Pin_Value('c',PIN_NO_0,HIGH);         /* Set PB0 high	*/
	_delay_us(10);								  /*  10 µs pulse   */
	DIO_vSet_Pin_Value('c',PIN_NO_0,LOW);        /*  Set PB0 low	*/
}





/*	Callback function that will be called in the ISR	*/
void ICU_Handler(void)
{
	
	
	if (g_state == 0)
	{
		
		/* Rising edge detected ==> echo pulse started	*/
		g_start_time = ICU_GetValue();
		
		/*	Setting to detect the falling edge	*/
		ICU_SetEdge(ICU_FALLING_EDGE);
		
		g_state = 1 ;
	} 
	
	else if (g_state == 1)
	{
		 /* Falling edge detected ? echo pulse ended		*/
		 g_end_time = ICU_GetValue();
		
		 /*
			 Calculation (distance in cm)
			 Sound velocity = 340.00 m/s = 34000 cm/s
			 The distance of Object (in cm) = (340000*Time)/2 =  17000 * Time
			 we have selected an internal 8MHz oscillator frequency for ATmega32, with
			 Prescaler F_CPU/8 for timer frequency. Then time to execute 1 instruction is 1 us.
			 So, the timer gets incremented after 1 us time elapse.
				= 17000 x (g_timeHigh) x 1 x 10^-6 cm
				= 0.017 x (g_timeHigh) cm
				= (g_timeHigh) / 58.8 cm
		 */
		 
		 g_pulse_width = g_end_time - g_start_time ;
		
		 g_distance_cm = (g_pulse_width * 128.0f) / 58.0f;  /* Convert to cm	*/
		
		
		/*	Setting to detect the rising edge	*/
		ICU_SetEdge(ICU_RISING_EDGE);
		
		g_state = 0 ;
		
	}
	
	
}




void UART_RX_Handler(u8 DataReceived)
{
	if (DataReceived == 'a')
	{
		SERVO_vRotateMotor('a', SERVO_ANGLE_0);
		SERVO_vRotateMotor('b', SERVO_ANGLE_0);
		DIO_vSet_Pin_Value('d', PIN_NO_3, ONE);
	}
	else if (DataReceived == 'b')
	{
		SERVO_vRotateMotor('a', SERVO_ANGLE_45);
		SERVO_vRotateMotor('b', SERVO_ANGLE_45);
		DIO_vSet_Pin_Value('d', PIN_NO_3, ZERO);
	}
	else if (DataReceived == 'c')
	{
		SERVO_vRotateMotor('a', SERVO_ANGLE_90);
		SERVO_vRotateMotor('b', SERVO_ANGLE_90);
		DIO_vSet_Pin_Value('d', PIN_NO_7, ONE);
	}
	else if (DataReceived == 'd')
	{
		SERVO_vRotateMotor('a', SERVO_ANGLE_135);
		SERVO_vRotateMotor('b', SERVO_ANGLE_135);
		DIO_vSet_Pin_Value('d', PIN_NO_7, ZERO);
	}
	else if (DataReceived == 'e')
	{
		SERVO_vRotateMotor('a', SERVO_ANGLE_180);
		SERVO_vRotateMotor('b', SERVO_ANGLE_180);
		DIO_vSet_Pin_Value('c', PIN_NO_0, ONE);
	}


}
