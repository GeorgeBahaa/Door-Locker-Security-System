/******************************************************************************
 *
 * File Name: control_mc2_main.c
 *
 * Description: main file for the functions used in Control Micro-controller  in electronic door open with pass project
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#include "application.h"

int main (void)
{
	app_init (); // Initialize UART,EEOROM,DC-Motor and Buzzer drivers

	if (check_pass_exist() == yes )// check if there is a password saved in the EEPROM
	{
		send_command(Start_Program_Pass); //Start program by asking for saved password
	}
	else if (check_pass_exist() == 0) //Password not found
	{
		send_command(Send_New_Pass); //Enter New Password
	}

	while(1)
	{

		receive_pass(); // receive password or options command

		if (pass_recieved[0]  == open_door_chosen )  //+ve chosen
		{
			send_command(Send_pass_to_open); //open door
		}
		else if (pass_recieved[0]  == change_pass_chosen ) //-ve chosen
		{
			send_command(Send_pass_to_reset); //ask for password to reset password
		}
		else if (pass_recieved[5] == start_pass_sent )
		{
			if (check_pass_correct() == yes ) //Check if entered pass is correct
			{
				send_command(Display_menu);//Display Menu
			}
			else
			{
				send_command(First_check_pass); //Check pass again
			}
		}
		else if (pass_recieved[5] == Send_New_Pass ) //New Passwords Enter
		{
			write_pass(); //Write New Password in EEPROM
			send_command(ReSend_New_Pass); //Check that entered password is correct
		}
		else if (pass_recieved[5] == resend_new_password ) // check confirmation of new password
		{
			if (check_pass_correct() == yes ) //Check if entered pass is correct
			{
				send_command(pass_is_changed); // pass is changed message
				send_command(Display_menu); //Show Menu again
			}
			else
			{
				send_command(Send_New_Pass); //Take New Password again
			}
		}
		else if  (pass_recieved[5]  == First_check_pass ) //check pass for first time
		{
			if (check_pass_correct() == yes ) //Check if entered pass is correct
			{
				send_command(Display_menu); //Show Menu again
			}
			else
			{
				send_command(Second_check_pass); //Check pass again
			}
		}
		else if  (pass_recieved[5]  == Second_check_pass ) //check pass for third time
		{
			if (check_pass_correct() == yes ) //Check if entered pass is correct
			{
				send_command(Display_menu); //Show Menu again
			}
			else
			{

				send_command(error_message_display); //error message
				buzzer_operate(); //start buzzer
				send_command(Display_menu); //Step 2 main options
			}

		}
		else if (pass_recieved[5]  == open_pass_sent ) // ask for pass when + chosen
		{
			if (check_pass_correct() == yes ) //Check if entered pass is correct
			{
				send_command(Display_motor_state); // Make MC1 display Motor State
				motor_operate(); //Start openning door
				send_command(Display_menu); //Show Menu again
			}
			else
			{
				send_command(First_check_pass); //Check pass again
			}
		}
		else if  (pass_recieved[5]  == reset_pass_sent ) // ask for pass when - chosen
		{
			if (check_pass_correct() == yes) //Check if entered pass is correct
			{
				send_command(Send_New_Pass); //Store New Password
			}
			else
			{
				send_command(First_check_pass); //Check pass again
			}
		}
	}
}

