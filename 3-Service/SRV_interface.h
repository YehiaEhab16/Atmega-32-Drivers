/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: TIMERS 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef SRV_INTERFACE_H_
#define SRV_INTERFACE_H_


#define SINGLE			1
#define REPEATED		2

void Timer_voidSchedule(u32 Microseconds, void (*Func)(void), u8 TYPE);

void Timer_ISR(void);
void Timer_ISR1(void);
void Timer_ISR2(void);


#endif
