/******************************************************************************
 *
 * File Name: application.h
 *
 * Description: Header file for the functions used in Control Micro-controller in electronic door open with pass project
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

# define EEPROM_PASSWORD_ADDRESS 0x22
# define Start_Program_Pass 'd'
# define Send_New_Pass '#'
# define ReSend_New_Pass 'e'
# define Display_menu 'a'
# define Send_pass_to_open 'b'
# define Display_motor_state 'c'
# define Send_pass_to_reset 'f'
# define First_check_pass '^'
# define Second_check_pass '&'
# define yes 'y'
# define open_door_chosen '+'
# define change_pass_chosen '-'
# define start_pass_sent 's'
# define open_pass_sent '%'
# define reset_pass_sent '@'
# define resend_new_password '!'
# define error_message_display 'x'
# define pass_is_changed 'm'

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

volatile uint8 pass_recieved[7]; //To store received pass
volatile uint8 command; // to send command
volatile uint8 eeprom_pass[7]; // to read data on EEPROM

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 *
 * Description :
 * Function to initialize UART,EEPROM,DC-Motor and Buzzer.
 */
void app_init (void);

/*
 * Description :
 * Function to receive password.
 */
void receive_pass(void);

/*
 * Description :
 * Function to send command.
 */
void send_command(uint8 data);

/*
 * Description :
 * Function to store password in EEPROM.
 */
void write_pass (void);

/*
 * Description :
 * Function to check if there is a password stored in EEPROM or not.
 */
uint8 check_pass_exist (void);

/*
 * Description :
 * Function to check if password entered by user is the same stored in EEPROM.
 */
uint8 check_pass_correct (void);

/*
 * Description :
 * Function to open and close the door
 */
void motor_operate (void);

/*
 * Description :
 * Function to start buzzer.
 */
void buzzer_operate (void);

/*
 * Description :
 * Function to use TIMER0 as required.
 */
void TIMER1_countProcessing(uint16 second_1);

/*
 * Description :
 * Function to use TIMER2 as required.
 */
void Timer1_Delay (uint16 seconds);

#endif /* APPLICATION_APPLICATION_H_ */
