 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	bits_5,bits_6,bits_7,bits_8,Reserved_4,Reserved_5,Reserved_6,bits_9
}UART_bit_data;

typedef enum{
	ONE,TWO
}UART_stop_bit;

typedef enum{
	DISABLED,RESERVED,ENABLED_EVEN,ENABLED_ODD
}UART_parity_test;

typedef enum
{
	Asynch_Normal,Asynch_Double,Synch_Master
}UART_operating_mood;

typedef struct
{
	uint32 baud_rate;
	UART_bit_data bit_data;
	UART_parity_test parity;
	UART_stop_bit stop_bit;
	UART_operating_mood operating_mode;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 *Str, uint8 size_of_string);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
