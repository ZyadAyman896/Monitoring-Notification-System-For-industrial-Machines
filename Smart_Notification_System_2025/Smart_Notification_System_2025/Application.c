/*
 * Smart_Notification_System_2025.c
 *
 * Created: 7/26/2025 4:20:23 AM
 * Author : Zyad Ayman
 */ 


#include "Application.h"


/************************************************************************/
/*                        global Variables			                    */
/************************************************************************/

/*	Variable for Uart received data	*/
volatile u8 DataReceived ;

/*	Variables for the ICU Peripheral	*/
volatile u8  g_state = 0 ;
volatile u16 g_start_time = 0;
volatile u16 g_end_time = 0;
volatile u16 g_pulse_width = 0;
volatile float32 g_distance_cm = 0;
volatile float32 g_last_distance = -1;  /* Initialized to an impossible value	*/


/*	flag used for ISR of EXTI 1 used for smoke flag	 */
volatile u8 g_smoke_flag = 0;

/*	flag used for ISR of EXTI 0 used for Vibration flag	 */
volatile u8 g_vibration_flag = 0;

/*	flag used for ISR of Timer1 CTC used for time of usage of machine flag	 */
volatile u8 g_Usage_Time_ofMachine_flag = 0;

/** Variable to hold the latest raw ADC value read from the temperature sensor (e.g., LM35) */
volatile u16 g_temp_adc_value = 0;

/** Variable to store the converted temperature in Celsius from the raw ADC value */
volatile float32 g_temp_celsius = 0;

/** Flag set by the Timer1 (CTC) ISR to signal that a new temperature value is available for processing */
volatile u8 g_CheckTempFlag = 0;






/************************************************************************/
/*                           Main code                                  */
/************************************************************************/


int main(void)
{
	
	
		/*	Variable for data received for UART		*/
		u8 DataReceived ;
		
		
		/*	LCD Init with 4-Bit mode	*/
		LCD_vInit();
	
		/*****************************************************************************/
		/**********************************ADC Init***********************************/

		/*	Configurations struct of ADC	*/
		ADC_Config_t adcConfig = {
			.ref = ADC_REF_AVCC,
			.adjust = ADC_RIGHT_ADJUST,
			.prescaler = ADC_PRESCALER_64 ,
			.interrupt_enable = 0	/*	Enable Interrupt for Adc	*/
		};

		/*	Init of ADC with specific configurations	*/
		ADC_vInit(&adcConfig);		

		
	
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
		
		/*	Configuring  Timer1	for CTC Mode with interrupt 	*/
		Timer1_Configurations config =
		{
			.Mode = TIMER1_MODE_CTC ,	/*	Normal Overflow Mode	*/
			.Interrupt_timer1 = TIMER1_INTERRUPT_ENABLED	/*	Interrupt Enabled	*/
			
		};
    
		/*	Initialization of Timer1	*/
		TIMER1_vInit(&config);
    
		/*	putting the value to get 1 sec	*/
		TIMER1_vSetValueCompareCTC(7813);
        
		/*	Setting Callback for timer ISR	*/
		TIMER1_vSetCompareCTCCallback(CTC_TimerHandler);
    
		/*	Prescaler Value	= 1024	*/
		TIMER1_vStart(TIMER1_PRESCALER_1024);
    
		/**********************************************************************************/
		/*******************************EXTI Init******************************************/	
	
		/*	Initializing External Interrupt 0	*/
		EXTI_vInit(EXTI_INT0,EXTI_FALLING_EDGE);	/*	Vibration Sensor	*/

		/*	Initializing External Interrupt 1	*/
		EXTI_vInit(EXTI_INT1,EXTI_FALLING_EDGE);	/*	Smoke Sensor	*/
	
		/*	Enabling EXTI0	*/
		EXTI_vEnable(EXTI_INT0);
	
		/*	Enabling EXTI1	*/
		EXTI_vEnable(EXTI_INT1);
	
		/*	Setting Callback Function to be executed by the ISR of INTERRUPT0	*/
		EXTI_vSetCallback(EXTI_INT0,EXTI0_Handler);		/*	Vibration Sensor	*/
	
		/*	Setting Callback Function to be executed by the ISR of INTERRUPT1	*/
		EXTI_vSetCallback(EXTI_INT1,EXTI1_Handler);		/*	Smoke Sensor	*/
		
		/************************************************************************/
		/*                          UART INIT                                   */
		/************************************************************************/
		
		/*	Initiallizing UART for using Bluetooth at baud rate of 9600 b/s	 */
		UART_vInit(UART_INTERRUPT_ENABLE,UART_BAUD_9600);
	
		/*	Setting the callback function to be called by the ISR	*/
		//UART_vSetRxCallback(UART_RX_Handler);    
	
    
		/*****************************************************************************/
	
			
		/*	Enable Global Interrupt		*/
		sei();	
		
		/*	small delay before LCD clear	*/
		_delay_ms(10);
	
		/*	Clear Display	*/
		LCD_vClear_Display();		
    
    while (1) 
    {
		
		
		/*------ Machine Usage Time Alert -------*/
		/*	Checking on activation of Much Time usage of machine Flag from the ISR or not	*/
		if (g_Usage_Time_ofMachine_flag == 1 )
		{
			/*	Disable global interrupts	*/
			cli();
			
						
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();
			
			/**/
			LED_vTurnOnLED('c',PIN_NO_5);
			
			_delay_ms(10);
			
			/*	Alerting for Much Time usage of machine on LCD	*/
			LCD_vBlinkCenteredStrings("Turn-Off","The Machine",3);
			
			
			/**/
			UART_vSendString("turn off");
			

			
			/**/
			_delay_ms(1000);

			/*	flag deactivation	*/
			g_Usage_Time_ofMachine_flag = 0;
			

			
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();	
			
			/**/
			_delay_ms(20);
			
			/*	Enable global interrupts again	*/
			sei();					
		}
		else if (g_Usage_Time_ofMachine_flag == 0)
		{
			/**/
			LED_vTurnOffLED('c',PIN_NO_5);
		}
		
		/*------ Vibration Alert -------*/
		/*	Checking on activation of High Vibration Flag from the ISR or not	*/
		if (g_vibration_flag == 1 ) 
		{
			/*	Disable global interrupts	*/
			cli();
			
			/*	flag deactivation	*/
			g_vibration_flag = 0;			

			/*	Enable global interrupts again	*/
			sei();		
			
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();
			
			/**/
			LED_vTurnOnLED('c', PIN_NO_4);
			
			/*	Alerting for High vibration detecting on LCD	*/
			LCD_vBlinkCenteredStrings("High", "Vibration", 3);
			
			/**/
			UART_vSendString("High Vibration");
			
			/**/
			_delay_ms(50);
		
				

			
		
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();	
			
			
			/**/
			_delay_ms(50);
			
			

								
		}
		else if (g_vibration_flag == 0 )
		{
			/**/
			LED_vTurnOffLED('c', PIN_NO_4);
			
		}
		
		/*------ Smoke Alert -------*/
		/*	Checking on activation of Smoke Detection Flag from the ISR or not	*/
		if (g_smoke_flag == 1 ) 
		{
			/*	Disable global interrupts	*/
			cli();
			
			
			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();
			
			/**/
			LED_vTurnOnLED('c', PIN_NO_3);
			
			/**/
			_delay_ms(2);
			
			/*	Alerting for Smoke detecting on LCD	*/
			LCD_vBlinkCenteredStrings("Smoke", "Detected", 3);
		
			
			UART_vSendString("Smoke Detected");
			
			/**/
			_delay_ms(50);
			
			
			/*	flag deactivation	*/
			g_smoke_flag = 0;
			
			

			/*	Clearing Display of LCD	 */
			LCD_vClear_Display();	
			
			/**/
			_delay_ms(20);
			
			/*	Enable global interrupts again	*/
			sei();		
		}
		else if (g_smoke_flag == 0)
		{
			/**/
			LED_vTurnOffLED('c', PIN_NO_3);
		}

		
		/*------ Ultrasonic Proximity Status Update -------*/
		/* Send Trigger pulse to Ultrasonic */
		Send_Trigger_Pulse();
		_delay_ms(30);

		/* Only update status if proximity changes */
		u8 is_near = (g_distance_cm <= CRITICAL_DISTANCE_CM);
		u8 was_near = (g_last_distance <= CRITICAL_DISTANCE_CM);

		if (is_near != was_near)
		{
			/*	Disable global interrupts	*/
			cli();
						
			/**/
			LCD_vSendString_xy(0,0,"                ");
			
			/**/
			_delay_ms(10);
			
			/**/
			LCD_vSendString_xy(0, 0, "Proximity :       ");

			if (is_near == 1 )
			{

				
				_delay_ms(10);
				LCD_vSendString_xy(0, 12, "N/OK");
				

				
				LED_vTurnOnLED('c', PIN_NO_1);
			
			}
			else if (is_near == 0 )
			{
				
				
				_delay_ms(10);
				LCD_vSendString_xy(0, 12, "OK");
				

				
				LED_vTurnOffLED('c', PIN_NO_1);
				
				
			}
			
			g_last_distance = g_distance_cm;  /*	Store for future comparison		*/ 
			
			/**/
			_delay_ms(20);
			
			/*	Enable global interrupts again	*/
			sei();
						
		}

		
		
		/*------ LCD Temp Status Update -------*/
		if (g_CheckTempFlag == 1 )
		{
			
			/*	Disable global interrupts	*/
			cli();			
			

			
			/**/
			g_CheckTempFlag = 0;

			/*	Start ADC conversion, compare value, and display	*/ 
			u16 temp = ADC_u16Read_Value(ADC_CHANNEL_2);
			u8 celsius = (u8)((temp * 500UL) / 1024); // Assuming 10mV/°C scaling

			if (celsius >= TEMP_THRESHOLD_C)
			{
				
				LCD_vSendString_xy(1,0,"                ");
				
				_delay_ms(10);
				
				LCD_vSendString_xy(1, 0, "Temp : Overheat ");
				
			
				
				LED_vTurnOnLED('c', PIN_NO_2);
			}
			else
			{
				LCD_vSendString_xy(1,0,"                ");
				_delay_ms(10);
				LCD_vSendString_xy(1, 0, "Temp : Normal   ");
				UART_vSendString("Temp Normal");
				
				
		
				
				LED_vTurnOffLED('c', PIN_NO_2);
			}
			
			_delay_ms(20);

			
			/*	Enable global interrupts again	*/
			sei();
		}
		
		
		
		/*	a delay For not confusing the ultrasonic	*/
	    _delay_ms(200);		
		
    
	
	
	}
	
	
	
}


/************************************************************************/
/*								ISRs									*/
/************************************************************************/

/*	Timer 1 CTC mode callback function to handle reaching max time of usage of the machine	*/
/* Timer1 CTC interrupt handler */
void CTC_TimerHandler()
{
	static u8 usage_counter = 0;
	static u8 temp_counter = 0;

	/* -------- Handle max usage time (30 seconds) -------- */
	usage_counter++;
	if (usage_counter >= 30)
	{
		g_Usage_Time_ofMachine_flag = 1;
		usage_counter = 0;
	}

	/* -------- Handle temperature check (every 20 seconds) -------- */
	temp_counter++;
	if (temp_counter >= 20)
	{
		g_CheckTempFlag = 1;
		temp_counter = 0;
	}
}



/*	Callback Function of the external interrupt 0 that senses the signal from the vibration sensor , then fires the interrupt */
void EXTI0_Handler()
{
	 /*	activating the flag */	
	 g_vibration_flag = 1;
}





/*	Callback Function of the external interrupt 1 that senses the signal from the smoke sensor , then fires the interrupt */
void EXTI1_Handler(void)
{
	/*	activating the flag */
	g_smoke_flag = 1 ;
	
}








/*	Callback function of the ICU interrupt that calculates the distance of the ultrasonic reading	*/
void ICU_Handler(void)
{
	
	/*	First State	*/
	if (g_state == 0)
	{
		
		/* Rising edge detected ==> echo pulse started	*/
		g_start_time = ICU_GetValue();
		
		/*	Setting to detect the falling edge	*/
		ICU_SetEdge(ICU_FALLING_EDGE);
		
		/*	To switch to the second state in the second interrupt fire	*/
		g_state = 1 ;
	} 
	
	/*	Second State	*/
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
		
		 g_distance_cm = (g_pulse_width * 128.0f) / 58.0f;  /* Convert distance to cm	*/
		
		
		/*	Setting to detect the rising edge	*/
		ICU_SetEdge(ICU_RISING_EDGE);
		
		/*	To switch to the second state in the first interrupt fire	*/
		g_state = 0 ;
		
	}
	
	
}



/*	UART RX Callback function for handling the data coming from the bluetooth module using UART	
void UART_RX_Handler(u8 DataReceived)
{
	switch (DataReceived)
	{
		/*	Rotate Motor on Channel OCR1A To Zero degrees	
		case 'a': SERVO_vRotateMotor('a', SERVO_ANGLE_0);   break;
		/*	Rotate Motor on Channel OCR1A To 45 degrees	
		case 'b': SERVO_vRotateMotor('a', SERVO_ANGLE_45);  break;
		/*	Rotate Motor on Channel OCR1A To 90 degrees	
		case 'c': SERVO_vRotateMotor('a', SERVO_ANGLE_90);  break;
		/*	Rotate Motor on Channel OCR1A To 135 degrees	
		case 'd': SERVO_vRotateMotor('a', SERVO_ANGLE_135); break;
		/*	Rotate Motor on Channel OCR1A To 180 degrees	
		case 'e': SERVO_vRotateMotor('a', SERVO_ANGLE_180); break;
	}
	

}
*/	



/************************************************************************/
/*							Used Functions                              */
/************************************************************************/

/*	Function That sends the trigger pulse for the ultrasonic distance	*/
void Send_Trigger_Pulse(void)
{
	DIO_vSet_Pin_Value('c',PIN_NO_0,HIGH);         /* Set PB0 high	*/
	_delay_us(10);								  /*  10 µs pulse   */
	DIO_vSet_Pin_Value('c',PIN_NO_0,LOW);        /*  Set PB0 low	*/
}
