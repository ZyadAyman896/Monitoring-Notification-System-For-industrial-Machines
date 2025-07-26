/*
 * LCD.c
 *
 * Created: 12/1/2023 11:16:57 AM
 *  Author: Zyad Ayman
 * 
 * 
 */ 

/************************************************************************/
/*                        #INCLUDES		                                */
/************************************************************************/
#define F_CPU 8000000UL

#include <math.h>

#include <util/delay.h>

#include "../DIO/DIO.h"


#include "LCD.h"


/************************************************************************/
/*                        FUNCTIONS IMPLEMENTATIONS                     */
/************************************************************************/



void LCD_vSendCommand(u8 copy_u8Char)
{
	/*
		...take care that if it is in FOUR bit mode	
		you must send the high nibble of instructions first 
		and then you take the low nibble and shift them left by four bits 
		as we send data or instructions on the 4 most significant pins of the port
	*/
	/* Rs == 0 */
	DIO_vSet_Pin_Value(CTRL_PORT,RS,ZERO); 
	/* sending  instructions */
	DIO_vSet_Port_Value(DATA_PORT,copy_u8Char);
	/* Enable */
	LCD_vEnable_Falling_Edge();
}

void LCD_vInit()
{
	#ifdef LCD_8BitMode
	
	_delay_ms(20); /* LCD power-on delay */ 
	
	/* MAKES PORTX OUTPUT */
	DIO_vSet_Port_Direction(DATA_PORT,0xff);
	/* MAKES PORTX OUTPUT FOR E and Rs */
	DIO_vSet_Port_Direction(CTRL_PORT,0x03);
	_delay_ms(40);
	LCD_vSendCommand(0b00111000); /* 0x38 */
	_delay_ms(1);
	LCD_vSendCommand(0b00001111); /* 0x0f */
	_delay_ms(1);
	LCD_vSendCommand(0b00000001);
	_delay_ms(2);
	#endif

	#ifdef LCD_4BitMode
	
	_delay_ms(20); /* LCD power-on delay */ 
	/* we can use one function instead those four lines for writing on half of the port and use inside it the write on most or least nibble */
	/* on default you always use from 4th pin of any port to the 7th port in 4-bit  init */
	/* I HAVE USED THOSE FOUR LINES TO NOT CORRUPT THE DIRECTION OF THE FIRST FOUR PINS OF THE PORT */
	/* WE MAKE THE 2ND FOUR PINS OF THE PORTA IS OUTPUT */
	DIO_vSet_Pin_Direction(DATA_PORT , PIN_NO_4 , OUTPUT);
	DIO_vSet_Pin_Direction(DATA_PORT , PIN_NO_5 , OUTPUT);
	DIO_vSet_Pin_Direction(DATA_PORT , PIN_NO_6 , OUTPUT);
	DIO_vSet_Pin_Direction(DATA_PORT , PIN_NO_7 , OUTPUT);
	/* MAKING (PIN0 ==> RS) AND (PIN1 ==> E) IN PORTB OUTPUT */
	DIO_vSet_Pin_Direction(CTRL_PORT , RS , OUTPUT); /* RS */
	DIO_vSet_Pin_Direction(CTRL_PORT , E , OUTPUT); /* E */
	/* BEGIN INIT */
	_delay_ms(40);
	/* Function Set */
	/* 1st and 2nd command no configurable options */
	LCD_vSendCommand(0b00100000);
	LCD_vSendCommand(0b00100000);
	/* bit 6 ==> Font of char(F) & bit 7 ==> line display (N)
	   F==> 5*7 ==> 0 or 5*10 ==> 1
	   N ==> 1 line ==> 0 or 2lines ==> 1 */
	LCD_vSendCommand(0x80); /* now i have edited i want two lines */
	_delay_us(40);	
	/* Display ON / OFF
	   D 4th bit, C 5th bit, B 6th bit
	   D ==> display on off .... if == 0 => off ...else ON
	   C ==> cursor display .... if == 0 => off ...else ON
	   B ==> cursor Blink .... if == 0 => off ...else ON */
	LCD_vSendCommand(0x00);
	LCD_vSendCommand(0xf0);
	_delay_us(40);	
	/* Display clear */
	LCD_vSendCommand(0x00);
	LCD_vSendCommand(0x10);
	_delay_ms(2);
	/* Entry mode set 
	   I/D 5th bit , SH 4th bit 
	   I/D ==> for 
	   SH ==> shift entire display left or right */
	LCD_vSendCommand(0x00);
	LCD_vSendCommand(0b01000000);
	#endif
}

void LCD_vSendChar(u8 copy_u8char)
{
	#ifdef LCD_8BitMode
	/* Rs = 1 */
	DIO_vSet_Pin_Value(CTRL_PORT,RS,ONE); 
	DIO_vSet_Port_Value(DATA_PORT,copy_u8char);
	/* Enable */
	LCD_vEnable_Falling_Edge();
	#endif

	#ifdef LCD_4BitMode 
	/* Rs = 1 */
	DIO_vSet_Pin_Value(CTRL_PORT,RS,ONE);
	/* Sending HIGH NIBBLE OF DATA */
	DIO_vSet_Port_Value(DATA_PORT,copy_u8char & 0xf0); 
	/* Enable */
	LCD_vEnable_Falling_Edge();
	_delay_ms(1);
	/* Sending LOW NIBBLE OF DATA */
	DIO_vSet_Port_Value(DATA_PORT, copy_u8char << FOUR); 
	/* Enable */
	LCD_vEnable_Falling_Edge();
	_delay_ms(2);
	#endif
}









void LCD_vSendString(Pu8 Address_u8char)
{
	while(*Address_u8char !='\0')
	{
		LCD_vSendChar(*Address_u8char);
		Address_u8char++;
	}
}









void LCD_vEnable_Falling_Edge()
{
	#ifdef LCD_8BitMode 
	/* Enable */
	DIO_vSet_Pin_Value(CTRL_PORT,PIN_NO_1,ONE);
	_delay_ms(1);
	DIO_vSet_Pin_Value(CTRL_PORT,PIN_NO_1,ZERO);
	#endif

	#ifdef LCD_4BitMode
	/* Enable */
	DIO_vSet_Pin_Value(CTRL_PORT,PIN_NO_1,ONE);
	_delay_ms(1);
	DIO_vSet_Pin_Value(CTRL_PORT,PIN_NO_1,ZERO);	
	#endif
}

void LCD_vMoveCursor(u8 copy_row , u8 copy_col)
{
	#ifdef LCD_8BitMode
	/* ROWS AND COLUMNS START FROM ZERO */
	/* AC is Address counter */
	u8 copy_AC = 0 , copy_value = 0 ;
	if (copy_row == ZERO) /* IF FIRST ROW */
		copy_AC = copy_col ;
	else /* IF SECOND ROW */
	{
		copy_AC = 0x40 + copy_col ;	/* MAKES AC BEGIN FROM 2ND ROW */	
	}
	copy_value = copy_AC  + 0x80 ; /* 0x80 to set ddram address */
	LCD_vSendCommand(copy_value);
	#endif

	#ifdef LCD_4BitMode
	u8 copy_AC = 0 , copy_value = 0 ;
	if (copy_row == ZERO) /* IF FIRST ROW */
		copy_AC = copy_col ;
	else /* IF SECOND ROW */
	{
		copy_AC = 0x40 + copy_col ;	/* MAKES AC BEGIN FROM 2ND ROW */
	}
	/* 0x80 to set ddram address */
	copy_value = copy_AC  + 0x80 ;
	/* Sending High nibble of instructions first */
	LCD_vSendCommand(copy_value & 0xf0);
	/* Sending low nibble of instructions second */
	LCD_vSendCommand(((copy_value & 0x0f) << FOUR));      
	#endif
}

void LCD_vCreateCustomChar(u8* Array , u8 copy_Location)
{
	u8 copy_AC = copy_Location * EIGHT , copy_value ;
	copy_value = copy_AC + 0x40 ;
	LCD_vSendCommand(copy_value);
	for (u8 i = 0 ; i < EIGHT ; i++)
	{
		LCD_vSendChar(Array[i]);
	}
}

u16 LCD_u16Get_Lengh_Of_Number(u16 Copy_u16Number)
{
	u16 Length = (Copy_u16Number == 0 ? 1 : 0);
	while (Copy_u16Number > 0)
	{
		Length++;
		Copy_u16Number /= 10;
	}
	return Length;
}

void LCD_vSendNumber(u16 Copy_u8Number)
{
	u8 str[16];
	u16 i = 0;
	u16 length = LCD_u16Get_Lengh_Of_Number(Copy_u8Number);

	while (length > 0)
	{
		u8 digit = Copy_u8Number % 10;
		str[i] = digit + '0';
		Copy_u8Number /= 10;
		length--;
		i++;
	}

	str[i] = '\0';

	u16 start = 0;
	u16 end = i - 1;
	while (start < end)
	{
		u8 temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}

	u16 j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == 0)
			LCD_vSendChar('0');
		else
			LCD_vSendChar(str[j]);
		j++;
	}
}

void LCD_vClear_Display()
{
	/* clearing display */
	#ifdef LCD_8BitMode
	LCD_vSendCommand(0x01);
	#endif
	#ifdef LCD_4BitMode
	LCD_vSendCommand(0x00);
	LCD_vSendCommand(0x10);
	#endif	
}


/* Function to shift the display left */
void LCD_vShiftDisplayLeft() {
    LCD_vSendCommand(0x18);  /* Command for shifting display left */
}

/* Function to shift the display right */
void LCD_vShiftDisplayRight() {
    LCD_vSendCommand(0x1C);  /* Command for shifting display right */
}



void LCD_vSendFloat(float number, u8 precision)
{
    float FractionalPart , FractionalScaled ;
    int IntegerPart , Roundednumber , Temporaryvariable ;
	u8 numberofdigits = 0 ;

    /** If number is negative, print '-' and make it positive **/
    if (number < 0)
    {
        LCD_vSendChar('-') ;
        number = -number ;
    }

    /** Get the integer part by type casting **/
    IntegerPart = (int)number ;

    /** Get the fractional part by subtracting integer part from the float **/
    FractionalPart = ( number - IntegerPart ) ;

    /** Print the integer part **/
    LCD_vSendNumber(IntegerPart) ;

    /** If precision > 0, print the decimal point **/
    if (precision > 0)
    {
        LCD_vSendChar('.') ;
    }

    /** Scale the fractional part to shift digits right of the decimal **/
    FractionalScaled = FractionalPart * pow(10, precision) ;

    /** Round the scaled fractional part to the nearest whole number **/
    Roundednumber = (int)(FractionalScaled + 0.5) ;

	/* Store the rounded number in a temporary variable */
	Temporaryvariable = Roundednumber ;

	/* Count the number of digits in the number */
	while( Temporaryvariable > 0 )
	{
    	numberofdigits++ ;
    	Temporaryvariable /= 10 ;
	}

	/* Add leading zeros if the number of digits is less than the desired precision */
	while ( numberofdigits < precision )
	{
    	LCD_vSendNumber( 0 ) ;
    	numberofdigits++ ;
	}


    /** Print the rounded fractional digits **/
    LCD_vSendNumber(Roundednumber);
}


/**
 * brief: Sends a string to a specific position on the LCD screen
 *
 * param: row  - The row number (0 or 1)
 * param: col  - The column number (0 to 15)
 * param: str  - Pointer to the null-terminated string to be displayed
 */

void LCD_vSendString_xy(u8 row, u8 col, Pu8 str)
{
    /**
     * Move the cursor to the desired DDRAM address
     * based on the row and column provided.
     */
    LCD_vMoveCursor(row, col);

    /**
     * Print the string from the current cursor position.
     * Characters will be written sequentially across the row.
     */
    LCD_vSendString(str);
}


/**
 * brief: Displays a string centered horizontally on a specific LCD row
 *
 * param: row  - The LCD row (0 or 1)
 * param: str  - Pointer to the null-terminated string to display
 */
void LCD_vPrintCentered(u8 row, Pu8 str)
{
    u8 len = 0;
    u8 pos;

    /**
     * Calculate the length of the string
     */
    while (str[len] != '\0')
    {
        len++;
    }

    /**
     * Calculate starting column to center the text
     * Assuming 16 columns: (16 - len) / 2
     */
    if (len < 16)
        pos = (16 - len) / 2;
    else
        pos = 0; /** If longer than 16, just print from start */

    /**
     * Move cursor to the calculated position
     */
    LCD_vMoveCursor(row, pos);

    /**
     * Print the string starting from that position
     */
    LCD_vSendString(str);
}


/*
 * brief: Blinks two centered strings on the LCD for a specified number of times
 *
 * param: str1      - String to display on row 0
 * param: str2      - String to display on row 1
 * param: blinks    - Number of times to blink the strings
 * param: delay_ms  - Delay in milliseconds between blink on and off
 */



void LCD_vBlinkCenteredStrings(Pu8 str1, Pu8 str2, u8 blinks)
{
	
	for (u8 i = 0; i < blinks; i++)
	{
		/* Display both strings centered	*/
		LCD_vPrintCentered(0, str1);
		LCD_vPrintCentered(1, str2);

		_delay_ms(400);

		/* Clear display to blink	*/
		LCD_vClear_Display();

		_delay_ms(400);
	}

	/* Optionally: Show the strings at the end of blinking	*/
	LCD_vPrintCentered(0, str1);
	LCD_vPrintCentered(1, str2);
}
