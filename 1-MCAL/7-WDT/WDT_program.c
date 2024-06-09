/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: WDT 				************/
/************		Version: 1.00	 		************/
/************		Date: 5-10-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_private.h"
#include "WDT_config.h"
#include "WDT_register.h"
#include "WDT_interface.h"

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	WDTCR = (1<<WDTCR_WDE) | (1<<WDTCR_WDTOE);

	WDTCR = 0;
}

u8 WDT_u8Sleep(u8 Copy_u8SleepTime)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8SleepTime<8)
	{
		WDTCR &= SLEEP_MASK;
		WDTCR |= Copy_u8SleepTime;
	}
	else
		Local_u8ErrorState=NOK;

	return Local_u8ErrorState;
}
