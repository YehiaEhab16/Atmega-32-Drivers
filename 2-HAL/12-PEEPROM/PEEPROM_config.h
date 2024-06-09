/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     			************/
/************		SWC: PEEPROM			************/
/************		Version: 1.00	 		************/
/************		Date: 2-1-2021 			************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef PEEPROM_CONFIG_H_
#define PEEPROM_CONFIG_H_


#define PEEPROM_DATA_PORT 		DIO_u8PORTC

#define PEEPROM_CTRL_PORT 		DIO_u8PORTB		//for OE, WE, A8, A9, A10

#define PEEPROM_ADDRESS_PORT 	DIO_u8PORTA		//for A7 -> A0

#define PEEPROM_OE				DIO_u8PIN7
#define PEEPROM_WE				DIO_u8PIN6		// should be output , initial high

#define PEEPROM_A10				DIO_u8PIN5
#define PEEPROM_A9				DIO_u8PIN4
#define PEEPROM_A8				DIO_u8PIN3


#endif
