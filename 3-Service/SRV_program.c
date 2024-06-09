/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: TIMERS 				************/
/************		Version: 1.00	 		************/
/************		Date: 24-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "TIMERS_interface.h"

#include "SRV_interface.h"

static u16 Global_u16Counter;
static u16 Global_u16Counter1;
static u16 Global_u16Counter2;

static u8 Function_Type;
static u8 Function_Type1;
static u8 Function_Type2;

static void (*ISR_FUNC)(void)=NULL;
static void (*ISR_FUNC1)(void)=NULL;
static void (*ISR_FUNC2)(void)=NULL;

void Timer_voidSchedule(u32 Microseconds, void (*Func)(void), u8 TYPE)
{
	static u8 Local_u8Flag=0;
	Local_u8Flag++;

	Timer_t Local_Timer_tDelay = {CTC, DIVIDE_BY_8, 250, NORMAL};

	if(Local_u8Flag==1)
	{
		Timer0_voidInit(&Local_Timer_tDelay);
		Timer_u8SetCallback(TIMER0_COMPARE_MATCH, &Timer_ISR);

		Global_u16Counter = (u16)(Microseconds / 200UL);

		if(Func!=NULL)
			ISR_FUNC = Func;

		Function_Type = TYPE;
	}

	else if(Local_u8Flag==2)
	{
		Timer1_voidInit(&Local_Timer_tDelay);
		Timer_u8SetCallback(TIMER1_COMPARE_MATCH_A, &Timer_ISR1);

		Global_u16Counter1 = (u16)(Microseconds / 200UL);

		if(Func!=NULL)
			ISR_FUNC1 = Func;

		Function_Type1 = TYPE;
	}

	else if(Local_u8Flag==3)
	{
		Timer2_voidInit(&Local_Timer_tDelay);
		Timer_u8SetCallback(TIMER2_COMPARE_MATCH, &Timer_ISR2);
		Local_u8Flag=0;

		Global_u16Counter2 = (u16)(Microseconds / 200UL);

		if(Func!=NULL)
			ISR_FUNC2 = Func;

		Function_Type2 = TYPE;
	}
}

void Timer_ISR(void)
{
	static volatile u16 Local_u16Counter=0;
	static volatile u8 Local_u8Flag=1;
	Local_u16Counter++;

	if((Local_u16Counter==Global_u16Counter) && (Local_u8Flag==1))
	{
		if(ISR_FUNC!=NULL)
			ISR_FUNC();

		Local_u16Counter=0;

		if(Function_Type==SINGLE)
			Local_u8Flag=2;
	}
}

void Timer_ISR1(void)
{
	static volatile u16 Local_u16Counter=0;
	static volatile u8 Local_u8Flag=1;
	Local_u16Counter++;

	if((Local_u16Counter==Global_u16Counter1) && (Local_u8Flag==1))
	{
		if(ISR_FUNC1 != NULL)
			ISR_FUNC1();

		Local_u16Counter=0;

		if(Function_Type1==SINGLE)
			Local_u8Flag=2;
	}
}

void Timer_ISR2(void)
{
	static volatile u16 Local_u16Counter=0;
	static volatile u8 Local_u8Flag=1;
	Local_u16Counter++;

	if((Local_u16Counter==Global_u16Counter2) && (Local_u8Flag==1))
	{
		if(ISR_FUNC2 != NULL)
			ISR_FUNC2();

		Local_u16Counter=0;

		if(Function_Type2==SINGLE)
			Local_u8Flag=2;
	}
}
