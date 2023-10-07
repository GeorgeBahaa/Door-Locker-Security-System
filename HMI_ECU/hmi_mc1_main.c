/******************************************************************************
 *
 * File Name: hmi_mc1_main.c
 *
 * Description: main file for the functions used in Human interface Micro-controller  in electronic door open with pass project
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#include "application.h"

volatile uint8 command; // variable to store received command

int main(void)
{

	app_init(); // Initialize UART and LCD drivers

	while(1)
	{

		command =  receive_command();  // rescieve command from mc2

		if (command == Start_Program_Pass)
		{
			send_password_start(); //send password to start program
		}
		else if (command == Send_New_Pass)
		{
			send_password_New(); // set new password
		}
		else if (command == ReSend_New_Pass)
		{
			resend_password_New(); //check new password is correct
		}
		else if (command == Display_menu)
		{
			main_options(); // show options menu
		}
		else if (command == Send_pass_to_open)
		{
			send_password_open(); // send password to open door
		}
		else if (command == Display_motor_state)
		{
			lcd_door_opening(); // display door status
		}
		else if (command == Send_pass_to_reset)
		{
			send_password_reset(); // send password to reset password
		}
		else if  (command == First_check_pass)
		{
			send_password_1(); // check pass for first time
		}
		else if  (command == Second_check_pass)
		{
			send_password_2(); // check pass for second time
		}
		else if (command == error_message_display)
		{
			error_message(); // display error message
		}
		else if (command == pass_is_changed)
		{
			pass_changed(); // pass is changed message
		}
	}
}
