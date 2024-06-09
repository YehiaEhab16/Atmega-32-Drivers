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
#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_


typedef struct MyStruct101
{
	u16 Periodicity;
	void (*TaskFunc)(void);
	u8 State;
	u8 FirstDelay;
}Task_t;

static void Scheduler(void);

#define TASK_SUSPENDED		0
#define TASK_RESUMED		1

#endif
