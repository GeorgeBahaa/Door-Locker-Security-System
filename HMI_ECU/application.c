/******************************************************************************
 *
 * File Name: application.c
 *
 * Description: Source file for the functions used in Human interface Micro-controller in electronic door open with pass project
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#include "application.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "Timer1.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

volatile uint8 key; //to store the pressed key from keypad
uint8 Timer1_complete = 0; //flag when timer1 finish

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize UART and LCD.
 */
void app_init (void)
{
	UART_ConfigType UART_Config = {9600,bits_8,DISABLED,ONE,Asynch_Double};

	/* Initialize ICU driver */
	UART_init(&UART_Config);

	LCD_init();
}

/*
 * Description :
 * Function to receive command.
 */
uint8 receive_command(void)
{
	return UART_recieveByte();
}

/*
 * Description :
 * Function to send password to start program.
 */
void send_password_start(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Password");
	LCD_moveCursor(1,0);

	do{

		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;

		if (i>=4 )
		{
			pass_sent[5]='s';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to send password to set new password
 */
void send_password_New(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter New Pass");
	LCD_moveCursor(1,0);

	do{
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;

		if (i>=4 )
		{
			pass_sent[5]='#';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to resend new password
 */
void resend_password_New(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"ReEnter New Pass");
	LCD_moveCursor(1,0);

	do{
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;
		if (i>=4 )
		{
			pass_sent[5]='!';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to send password check for the first time
 */
void send_password_1(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Re-Enter Pass");
	LCD_moveCursor(1,0);
	do{
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;

		if (i>=4 )
		{
			pass_sent[5]='^';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to send password check for the second time
 */
void send_password_2(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Re-Enter Pass");
	LCD_moveCursor(1,0);
	do{
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;
		if (i>=4 )
		{
			pass_sent[5]='&';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to display options and send selected one.
 */
void main_options(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+: Open Door");
	LCD_displayStringRowColumn(1,0,"-: Change Pass");

	do {
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		if (key == '+'||key =='-')
		{
			pass_sent[0] = key;

			pass_sent[5]='m';
			pass_sent[6]='n'; //send n to end string

			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to send password to open door
 */
void send_password_open(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Open Pass");
	LCD_moveCursor(1,0);
	do{
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;
		if (i>=4 )
		{
			pass_sent[5]='%';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to send password to reset password
 */
void send_password_reset(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 i=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Old Pass");
	LCD_moveCursor(1,0);
	do{
		key = KEYPAD_getPressedKey();

		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		Timer1_Delay(500);

		LCD_displayCharacter('*');

		pass_sent[i] = key;
		if (i>=4 )
		{
			pass_sent[5]='@';
			pass_sent[6]='n'; //send n to end string

			/*
			 * loop waiting to press enter key
			 * enter key is =
			 */
			do {
				key = KEYPAD_getPressedKey();

				/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
				Timer1_Delay(500);
			}while ( (key != '=') );
			/* Send the pressed key to MC2 through UART */
			UART_sendString(pass_sent,7);
			break;
		}
		i++;
	}while ( (key >= 0) && (key<= 9));
	Timer1_deInit();
}

/*
 * Description :
 * Function to display motor state
 */
void lcd_door_opening(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_1024,CMP_1,7812,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Door is Opening");

	Timer1_Delay (15);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Door is Open");

	Timer1_Delay (3);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Door is Closing");

	Timer1_Delay (15);

	Timer1_deInit();
}

/*
 * Description :
 * Function to show error message if pass is incorrect for 3 times
 */
void error_message(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_1024,CMP_1,7812,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,6,"Error");

	LCD_displayStringRowColumn(1,1,"Pass is wrong");

	Timer1_Delay (60);

	Timer1_deInit();
}

/*
 * Description :
 * Function to show state that changing pass done
 */
void pass_changed(void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_1024,CMP_1,7812,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,2,"Pass changed");
	Timer1_Delay (5);

	Timer1_deInit();
}
/*
 * Description :
 * Function to use TIMER1 as required.
 */
void TIMER1_countProcessing(uint16 second_1) {
	g1_tick++;
	if (g1_tick == (second_1))
	{
		Timer1_complete =1;
		g1_tick = 0; //clear the tick counter again to count a new 0.5 second
	}
}

/*
 * Description :
 * Function to start Timer1 and count as given.
 */
void Timer1_Delay (uint16 seconds)
{
	Timer1_complete =0;
	g1_tick = 0;
	second_1 = seconds;
	while (Timer1_complete != 1){}
}
