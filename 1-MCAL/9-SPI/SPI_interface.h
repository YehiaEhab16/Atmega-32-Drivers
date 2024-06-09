/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: SPI 				************/
/************		Version: 1.00	 		************/
/************		Date: 8-10-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


#define SPI_MASTER		1
#define SPI_SLAVE		2

void SPI_voidInit(u8 Copy_u8Role);

u8 SPI_u8Transcieve(u8 Copy_u8Data, u8* Copy_pu8RecivedData);

u8 SPI_u8TranscieveBufferSynch(u8* Copy_pu8Data, u8* Copy_pu8RecivedData, u8 Copy_u8BufferSize);

//Must enable global interrupt
u8 SPI_u8TranscieveBufferAsynch(u8* Copy_pu8Data, u8* Copy_pu8RecivedData, u8 Copy_u8BufferSize, void (*Copy_pvNotificationFunc)(void));


#endif
