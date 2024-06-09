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
#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_


#define SPCR			*((volatile u8*) 0x2D)
#define SPCR_SPIE		7		//Interrupt Enable
#define SPCR_SPE		6		//Enable
#define SPCR_DORD		5		//Data Order
#define SPCR_MSTR		4		//Master/Salve Select
#define SPCR_CPOL		3		//Clock Polarity
#define SPCR_CPHA		2		//Clock Phase
#define SPCR_SPR1		1		//Clock Select
#define SPCR_SPR0		0		//Clock Select

#define SPDR			*((volatile u8*) 0x2F)
#define SPDR_MSB		7
#define SPDR_LSB		0

#define SPSR			*((volatile u8*) 0x2E)
#define SPSR_SPIF		7		//Interrupt Flag
#define SPSR_WCOL		6		//Write Collision Flag
#define SPSR_SPI2X		0		//Double Speed


#endif
