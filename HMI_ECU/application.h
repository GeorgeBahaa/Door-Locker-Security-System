/******************************************************************************
 *
 * File Name: application.h
 *
 * Description: Header file for the functions used in Human interface Micro-controller in electronic door open with pass project
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

# define Start_Program_Pass 'd'
# define Send_New_Pass '#'
# define ReSend_New_Pass 'e'
# define Display_menu 'a'
# define Send_pass_to_open 'b'
# define Display_motor_state 'c'
# define Send_pass_to_reset 'f'
# define First_check_pass '^'
# define Second_check_pass '&'
# define error_message_display 'x'
# define pass_is_changed 'm'

/*******************************************************************************
 *                         Variables Declaration                                   *
 *******************************************************************************/

volatile uint8 pass_sent[7];//To store pass

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize UART and LCD.
 */
void app_init (void);

/*
 * Description :
 * Function to receive command.
 */
uint8 receive_command(void);

/*
 * Description :
 * Function to send password to start program.
 */
void send_password_start(void);

/*
 * Description :
 * Function to send password to set new password
 */
void send_password_New(void);

/*
 * Description :
 * Function to resend new password
 */
void resend_password_New(void);

/*
 * Description :
 * Function to send to password check for the first time
 */
void send_password_1(void);

/*
 * Description :
 * Function to send password to check for the second time
 */
void send_password_2(void);

/*
 * Description :
 * Function to display options and send selected one.
 */
void main_options(void);

/*
 * Description :
 * Function to send password to open door
 */
void send_password_open(void);

/*
 * Description :
 * Function to send password to reset password
 */
void send_password_reset(void);

/*
 * Description :
 * Function to display motor state
 */
void lcd_door_opening(void);

/*
 * Description :
 * Function to show error message if pass is incorrect for 3 times
 */
void error_message(void);

/*
 * Description :
 * Function to show state that changing pass done
 */
void pass_changed(void);
/*
 * Description :
 * Function to use TIMER0 as required.
 */
void TIMER1_countProcessing(uint16 second_1);

/*
 * Description :
 * Function to start Timer1 and count as given.
 */
void Timer1_Delay (uint16 seconds);

#endif /* APPLICATION_APPLICATION_H_ */
