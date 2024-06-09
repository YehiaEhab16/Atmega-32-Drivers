/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: DAC			************/
/************		Version: 1.00	 		************/
/************		Date: 21-9-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DAC_config.h"
#include "DAC_interface.h"
#include "DAC_private.h"

void DAC_voidSetAnalogVolt(u16 Copy_u16Volt)
{
	if(Copy_u16Volt>=5000)
		Copy_u16Volt=4999;

	u8 Local_u8DigitalValue = ((u32)Copy_u16Volt *256UL) / 5000UL;

	DIO_u8SetPortValue(DAC_PORT, Local_u8DigitalValue);
}

void DAC_voidSetPortValue(u8 Copy_u8PortValue)
{
	DIO_u8SetPortValue(DAC_PORT, Copy_u8PortValue);
}
