/*
 * LCD.h
 *
 * Created: 12/1/2023 11:17:13 AM
 *  Author: Zyad Ayman
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../Helping Files/Utils.h"

#include "../Helping Files/std_types.h"


/************************************************************************/
/*                        CONFIGURATIONS                                */
/************************************************************************/


/*  UNCOMMENT FIRST OR SECOND LINE TO CHOOSE THE MODE   */

/* #define  LCD_8BitMode */
#define  LCD_4BitMode 



/*************Choosing Ports and Pins Used*********************/

#define DATA_PORT 'A'
#define CTRL_PORT 'B'

#define RS PIN_NO_0
#define E  PIN_NO_1
#define RW PIN_NO_2


/************************************************************************/
/*                        FUNCTIONS PROTOTYPES                          */
/************************************************************************/

/** 
 * brief: Initializes the LCD in either 4-bit or 8-bit mode.
 */
void LCD_vInit();

/** 
 * brief: Sends a single character to be displayed on the LCD.
 * param: copy_u8char The character to display.
 */
void LCD_vSendChar(u8 copy_u8char);

/** 
 * brief: Sends a null-terminated string to the LCD.
 * param: copy_u8char Pointer to the string to be displayed.
 */
void LCD_vSendString(u8* copy_u8char);

/** 
 * brief: Sends a command byte to the LCD to control its operation.
 * param: copy_u8char The command to send.
 */
void LCD_vSendCommand(u8 copy_u8char);

/** 
 * brief: Generates the falling edge pulse to trigger LCD command or data latch.
 */
void LCD_vEnable_Falling_Edge();

/** 
 * brief: Moves the LCD cursor to a specific row and column.
 * param: copy_row The row number (0 or 1).
 * param: copy_col The column number (0–15 typically).
 */
void LCD_vMoveCursor(u8 copy_row , u8 copy_col);

/** 
 * brief: Creates a custom character in CGRAM and stores it at a specific location.
 * param: Array Pointer to an array of 8 bytes representing the character pattern.
 * param: copy_Location CGRAM location (0 to 7) to store the character.
 */
void LCD_vCreateCustomChar(u8* Array , u8 copy_Location);

/** 
 * brief: Displays an unsigned integer number on the LCD.
 * param: Copy_u8Number The number to display.
 */
void LCD_vSendNumber(u16 Copy_u8Number);

/** 
 * brief: Calculates the number of digits in an unsigned integer.
 * param: Copy_u16Number The number whose length is to be calculated.
 * return: The number of digits in the input number.
 */
u16 LCD_u16Get_Lengh_Of_Number(u16 Copy_u16Number);

/** 
 * brief: Clears the LCD screen.
 */
void LCD_vClear_Display();

/** 
 * brief: Shifts the entire display content one position to the left.
 */
void LCD_vShiftDisplayLeft();

/** 
 * brief: Shifts the entire display content one position to the right.
 */
void LCD_vShiftDisplayRight();

/** 
 * brief: Displays a floating-point number on the LCD with a given precision.
 * param: number The float number to be displayed.
 * param: precision Number of digits to display after the decimal point.
 */
void LCD_vSendFloat(float number, u8 precision);


/**
 * brief: Sends a string to a specific position on the LCD screen
 *
 * param: row  - The row number (0 or 1)
 * param: col  - The column number (0 to 15)
 * param: str  - Pointer to the null-terminated string to be displayed
 */

void LCD_vSendString_xy(u8 row, u8 col, Pu8 str);




/**
 * brief: Displays a string centered horizontally on a specific LCD row
 *
 * param: row  - The LCD row (0 or 1)
 * param: str  - Pointer to the null-terminated string to display
 */
void LCD_vPrintCentered(u8 row, Pu8 str);



/*
 * brief: Blinks two centered strings on the LCD for a specified number of times
 *
 * param: str1      - String to display on row 0
 * param: str2      - String to display on row 1
 * param: blinks    - Number of times to blink the strings
 * param: delay_ms  - Delay in milliseconds between blink on and off
 */

void LCD_vBlinkCenteredStrings(Pu8 str1, Pu8 str2, u8 blinks);




/************************************************************************/
/*                        FUTURE FUNCTIONS PROTOTYPES                   */
/************************************************************************/

/*


LCD_vScrollText(const Uu* str, uint8_t row)
LCD_vSendBinary(uint8_t value)
LCD_vSendHex(uint8_t value)



*/

#endif /* LCD_H_ */
