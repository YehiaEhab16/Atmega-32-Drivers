/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: SPI 				************/
/************		Version: 1.00	 		************/
/************		Date: 8-10-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_register.h"

static u8 SPI_u8STATE = IDLE;

static u8* Global_pu8Data=NULL;
static u8* Global_pu8ReceivedData=NULL;
static u8 Global_u8BufferSize;
static void (*SPI_pvCallBackFunc)(void)=NULL;

static u8 Global_u8Index;

void SPI_voidInit(u8 Copy_u8Role)
{
	//Set master or slave mode
	if(Copy_u8Role==SPI_MASTER)
	{
	SET_BIT(SPCR, SPCR_MSTR);

	//Clock speed
	#if SPI_PRESCALAR==DIVIDE_BY_4
	CLR_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);

	#elif SPI_PRESCALAR==DIVIDE_BY_16
	SET_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);

	#elif SPI_PRESCALAR==DIVIDE_BY_64
	CLR_BIT(SPCR, SPCR_SPR0);
	SET_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);

	#elif SPI_PRESCALAR==DIVIDE_BY_128
	SET_BIT(SPCR, SPCR_SPR0);
	SET_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);

	#elif SPI_PRESCALAR==DIVIDE_BY_2
	CLR_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	SET_BIT(SPSR, SPSR_SPI2X);

	#elif SPI_PRESCALAR==DIVIDE_BY_8
	SET_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	SET_BIT(SPSR, SPSR_SPI2X);

	#elif SPI_PRESCALAR==DIVIDE_BY_32
	CLR_BIT(SPCR, SPCR_SPR0);
	SET_BIT(SPCR, SPCR_SPR1);
	SET_BIT(SPSR, SPSR_SPI2X);

	#endif
	}

	else if(Copy_u8Role==SPI_SLAVE)
		CLR_BIT(SPCR, SPCR_MSTR);

	//Clock Polarity
	#if CLK_POLARITY==0
	CLR_BIT(SPCR, SPCR_CPOL);

	#elif CLK_POLARITY==1
	SET_BIT(SPCR, SPCR_CPOL);

	#endif

	//Clock Phase
	#if CLK_PHASE==0
	CLR_BIT(SPCR, SPCR_CPHA);

	#elif CLK_PHASE==1
	SET_BIT(SPCR, SPCR_CPHA);

	#endif

	//Data Order
	#if DATA_ORDER==LSB_FIRST
	SET_BIT(SPCR, SPCR_DORD);

	#elif DATA_ORDER==MSB_FIRST
	CLR_BIT(SPCR, SPCR_DORD);

	#endif

	//SPI Enable
	SET_BIT(SPCR, SPCR_SPE);
}

u8 SPI_u8Transcieve(u8 Copy_u8Data, u8* Copy_pu8RecivedData)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter=0;

	if(Copy_pu8RecivedData!=NULL)
	{
		if(SPI_u8STATE==IDLE)
		{
			SPI_u8STATE=BUSY;
			//Send the Data
			SPDR = Copy_u8Data;

			//Wait until transfer is complete
			while(((GET_BIT(SPSR, SPSR_SPIF))==0) && (Local_u32Counter<SPI_u32Timeout))
			{
				Local_u32Counter++;
			}
			if(Local_u32Counter==SPI_u32Timeout)
				Local_u8ErrorState = TIMEOUT_STATE;
			else
				*Copy_pu8RecivedData = SPDR;	//return the received data

			SPI_u8STATE=IDLE;
		}
		else
			Local_u8ErrorState=BUSY_STATE;
	}
	else
		Local_u8ErrorState=NULL_POINTER;

	return Local_u8ErrorState;
}

u8 SPI_u8TranscieveBufferSynch(u8* Copy_pu8Data, u8* Copy_pu8RecivedData, u8 Copy_u8BufferSize)
{
	u8 Local_u8ErrorState = OK, Local_u8Counter;

	if((Copy_pu8Data!=NULL) && (Copy_pu8RecivedData!=NULL))
		for(Local_u8Counter=0;Local_u8Counter<Copy_u8BufferSize; Local_u8Counter++)
			SPI_u8Transcieve(Copy_pu8Data[Local_u8Counter], &Copy_pu8RecivedData[Local_u8Counter]);

	else
		Local_u8ErrorState = NULL_POINTER;

	return Local_u8ErrorState;
}

u8 SPI_u8TranscieveBufferAsynch(u8* Copy_pu8Data, u8* Copy_pu8RecivedData, u8 Copy_u8BufferSize, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = OK;

	if((Copy_pu8Data!=NULL) && (Copy_pu8RecivedData!=NULL) && (Copy_pvNotificationFunc!=NULL))
	{
		if(SPI_u8STATE==IDLE)
		{
			SPI_u8STATE=BUSY;

			Global_pu8Data = Copy_pu8Data;
			Global_pu8ReceivedData = Copy_pu8RecivedData;
			Global_u8BufferSize = Copy_u8BufferSize;
			SPI_pvCallBackFunc = Copy_pvNotificationFunc;

			Global_u8Index = 0;

			SPDR = Global_pu8Data[Global_u8Index];

			//Enable SPI Interrupt Enable
			SET_BIT(SPCR, SPCR_SPIE);
		}
		else
			Local_u8ErrorState = BUSY_STATE;
	}
	else
		Local_u8ErrorState = NULL_POINTER;

	return Local_u8ErrorState;
}

void __vector_12 (void)		__attribute__((signal));
void __vector_12 (void)
{
	Global_pu8ReceivedData[Global_u8Index] = SPDR;

	//Increment Index
	Global_u8Index++;

	//Check size
	if(Global_u8Index==Global_u8BufferSize)
	{
		//State is Idle
		SPI_u8STATE=IDLE;

		//Disable Interrupt Enable
		CLR_BIT(SPCR, SPCR_SPIE);

		//Invoke Notification Function
		SPI_pvCallBackFunc();
	}
	else
		SPDR = Global_pu8Data[Global_u8Index];
}
