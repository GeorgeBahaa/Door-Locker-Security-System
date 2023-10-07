/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.c
 *
 * Description: Source file for the Timer1 driver
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#include "Timer1.h"
#include"avr/io.h"
#include "common_macros.h"
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g1_callBackPtr)(uint16) = NULL_PTR;

/* global variable contain the ticks count of the timer1 */
uint16 g1_tick = 0;

/* global variable contain the number of seconds to count in Timer1*/
uint16 second_1 =0 ;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect) {
	if (g1_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g1_callBackPtr)(second_1); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect) {
	if (g1_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g1_callBackPtr)(second_1); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPB_vect) {
	if (g1_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g1_callBackPtr)(second_1); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	/*  timer1 mood as required in configuration */
	TCCR1A = (TCCR1A & 0xFC) | ((Config_Ptr->mode & 0x03));
	TCCR1B = (TCCR1B & 0xE7) | ((Config_Ptr->mode & 0x0C) << 1);

	/*  timer1 Compare as required in configuration */
	TCCR1A = (TCCR1A & 0x3F) | ((Config_Ptr->a_compare_mode)<<6);
	TCCR1A = (TCCR1A & 0xCF) | ((Config_Ptr->b_compare_mode)<<4);

	/*  timer1 prescaler as required in configuration */
	TCCR1B = (TCCR1B & 0xF8) | ((Config_Ptr->prescaler));

	/*  timer1 initial value as required in configuration */
	TCNT1 = ((Config_Ptr->initial_value));

	/*NON PWM*/
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);

	/*  timer1 enable  as required in configuration */
	if((Config_Ptr->mode == CMP_1) | (Config_Ptr->mode == CMP_2)){
		if ((Config_Ptr->channel)==Channel_A){
			TIMSK |= (1 << OCIE1A);
			/*  timer1 first compare value as required in configuration */
			OCR1A =  (Config_Ptr->a_compare_value);
		}
		else
		{
			TIMSK |= (1 << OCIE1B);
			/*  timer1 first compare value as required in configuration */
			OCR1B =  (Config_Ptr->b_compare_value);
		}
	}
	else {
		TIMSK |= (1 << TOIE1)| (1<<TICIE1);
	}
	SREG |= (1 << 7); //Enable global interrupts in MC by setting the I-Bit.
}

/*
 * Description :
 * Function to De-initialize Timer1.
 */
void Timer1_deInit(void){
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1 << OCIE1B) & ~(1 << TOIE1) & ~(1 << TICIE1) & ~(1 << OCIE1A);
}

/*
 * Description:
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void (*a_ptr)(uint16)) {
	/* Save the address of the Call back function in a global variable */
	g1_callBackPtr = a_ptr;
}
