/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the Timer1 driver
 *
 * Author: George Bahaa
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include"std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	No_CLK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXT_FALLING,EXT_RISING
}Timer1_Prescaler;

typedef enum{
	Normal,PWM_8,PWM_9,PWM_10,CMP_1,FPWM_8,FPWM_9,FPWM_10,PWM_PF_1,PWM_PF_2,PWM_P_1,PWM_P_2,CMP_2,Reserved,FPWM_1,FPWM_2
}Timer1_Mode;

typedef enum {
	Channel_A,Channel_B
}TIMER1_Channel;

typedef enum {
	Normal_compare, Toggle, Clear, Set
} TIMER_compare_mode;

typedef struct {
	uint16 initial_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
	uint16 a_compare_value;
	uint16 b_compare_value;
	TIMER1_Channel channel;
	TIMER_compare_mode a_compare_mode;
	TIMER_compare_mode b_compare_mode;
} Timer1_ConfigType;


/* global variable contain the ticks count of the timer1 */
extern uint16 g1_tick;

/* global variable contain the number of seconds to count in Timer1 */
extern uint16 second_1;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description:
 * Function to disable the Timer1
 */
void Timer1_deInit(void);

/*
 * Description:
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void (*a_ptr)(uint16));

#endif /* TIMER_H_ */
