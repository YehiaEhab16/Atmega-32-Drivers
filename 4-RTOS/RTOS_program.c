/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: RTOS Stack  		************/
/************		SWC: RTOS 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-3-2021 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "TIMERS_interface.h"

#include "RTOS_config.h"
#include "RTOS_interface.h"
#include "RTOS_private.h"
#include "RTOS_register.h"

Task_t SystemTasks [TASK_NUM] = {{NULL}};

void RTOS_voidStart(void)
{
	Timer_u8SetCallback(TIMER0_COMPARE_MATCH, &Scheduler);
	Timer_t Zero = {CTC , DIVIDE_BY_1024, 10, NORMAL};
	Timer0_voidInit(&Zero);
}

u8 RTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, void (*Copy_pvTaskFunc)(void), u8 Copy_u8FirstDelay)
{
	u8 Local_u8ErrorState=OK;

	if(SystemTasks[Copy_u8Priority].TaskFunc == NULL)
	{
		SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
		SystemTasks[Copy_u8Priority].TaskFunc = Copy_pvTaskFunc;
		SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
		SystemTasks[Copy_u8Priority].FirstDelay = Copy_u8FirstDelay;
	}
	else
		Local_u8ErrorState = NOK;

	return Local_u8ErrorState;
}

static void Scheduler(void)
{
	u8 Local_u8TaskCounter;

	for(Local_u8TaskCounter=0;Local_u8TaskCounter<TASK_NUM;Local_u8TaskCounter++)
		if(SystemTasks[Local_u8TaskCounter].State == TASK_RESUMED)
		{
			if(SystemTasks[Local_u8TaskCounter].FirstDelay==0)
			{
				if(SystemTasks[Local_u8TaskCounter].TaskFunc!=NULL)
				{
					SystemTasks[Local_u8TaskCounter].TaskFunc();
					SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity - 1;

				}
			}
			else
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
		}
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority] = TASK_RESUMED;
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority] = TASK_SUSPENDED;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].TaskFunc = NULL;
}
