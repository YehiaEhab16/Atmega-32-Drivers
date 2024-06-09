/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: RTOS Stack  		************/
/************		SWC: RTOS 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-3-2021 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_


void RTOS_voidStart(void);

u8 RTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void), u8 Copy_u8FirstDelay);

void RTOS_voidResumeTask(u8 Copy_u8Priority);

void RTOS_voidSuspendTask(u8 Copy_u8Priority);

void RTOS_voidDeleteTask(u8 Copy_u8Priority);

#endif
