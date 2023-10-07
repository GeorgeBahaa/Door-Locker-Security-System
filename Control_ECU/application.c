/******************************************************************************
 *
 * File Name: application.c
 *
 * Description: Source file for the functions used in Control Micro-controller in electronic door open with pass project
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#include "application.h"
#include "buzzer.h"
#include "DC_Motor.h"
#include "external_eeprom.h"
#include "uart.h"
#include "Timer1.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
uint8 Timer1_complete = 0; //flag when timer1 finish

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize UART,EEPROM,DC-Motor and Buzzer.
 */
void app_init (void)
{
	UART_ConfigType UART_Config = {9600,bits_8,DISABLED,ONE,Asynch_Double};

	/* Initialize ICU driver */
	UART_init(&UART_Config);

	EEPROM_init();

	DcMotor_Init();

	Buzzer_init();

}

/*
 * Description :
 * Function to receive password.
 */
void receive_pass(void)
{
	/* Receive the pressed key from MC1 through UART */
	UART_receiveString(pass_recieved);
}

/*
 * Description :
 * Function to send command.
 */
void send_command(const uint8 data)
{
	UART_sendByte(data);
}

/*
 * Description :
 * Function to store password in EEPROM.
 */
void write_pass (void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	uint8 x = 0;
	while (x<6){
		EEPROM_writeByte(EEPROM_PASSWORD_ADDRESS+x,pass_recieved[x]);
		Timer1_Delay(20); /* Delay between every operation on EEPROM */

		EEPROM_readByte(EEPROM_PASSWORD_ADDRESS+x,&eeprom_pass[x]);
		Timer1_Delay(20); /* Delay between every operation on EEPROM */

		x++;
	}
	Timer1_deInit();
}

/*
 * Description :
 * Function to check if there is a password stored in EEPROM or not.
 */
uint8 check_pass_exist (void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_8,CMP_1,1000,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	int x=0;
	uint8 found = 0;
	while (x<6){
		EEPROM_readByte(EEPROM_PASSWORD_ADDRESS+x,&eeprom_pass[x]);
		Timer1_Delay(20); /* Delay between every operation on EEPROM */

		x++;
	}

	if (eeprom_pass[5]=='#')
	{
		found ='y';
	}
	Timer1_deInit();
	return found;
}

/*
 * Description :
 * Function to check if password entered by user is the same stored in EEPROM.
 */
uint8 check_pass_correct (void)
{
	int i=0;
	uint8 correct = 0;
	while (i<5)
	{
		if (pass_recieved[i]!=eeprom_pass[i])
		{
			correct = 0;
			break;
		}
		correct ='y';
		i++;
	}
	return correct;
}

/*
 * Description :
 * Function to open and close the door
 */
void motor_operate (void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_1024,CMP_1,7812,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	DcMotor_Rotate(DC_MOTOR_CW,100);

	Timer1_Delay (15);

	DcMotor_Rotate(DC_MOTOR_OFF,0);

	Timer1_Delay (3);

	DcMotor_Rotate(DC_MOTOR_ACW,100);

	Timer1_Delay (15);

	DcMotor_Rotate(DC_MOTOR_OFF,0);

	Timer1_deInit();
}

/*
 * Description :
 * Function to start buzzer.
 */
void buzzer_operate (void)
{
	Timer1_ConfigType TIMER1_Config = {0,F_CPU_1024,CMP_1,7812,0,Channel_A,Normal_compare,Normal_compare};

	Timer1_init(&TIMER1_Config); /* initialize TIMER driver */

	Timer1_setCallBack(TIMER1_countProcessing);

	Buzzer_ON();

	Timer1_Delay (60);

	Buzzer_OFF();

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
		Timer1_complete = 1;
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
