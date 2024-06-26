/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: KPD 				************/
/************		Version: 1.00	 		************/
/************		Date: 1-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_


#define KPD_BUTONS_VAL		{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}

#define NO_PRESSED_KEY		0xff  // number not in keypad numbers above

#define KPD_MODE			INSTANT  //HOLD or Instant

#define KPD_PORT			DIO_u8PORTD

//Column pins output high, 	Row pins input pulled up
#define COLUMN_PIN0			DIO_u8PIN3
#define COLUMN_PIN1			DIO_u8PIN2
#define COLUMN_PIN2			DIO_u8PIN1
#define COLUMN_PIN3			DIO_u8PIN0

#define ROW_PIN0			DIO_u8PIN4
#define ROW_PIN1			DIO_u8PIN5
#define ROW_PIN2			DIO_u8PIN6
#define ROW_PIN3			DIO_u8PIN7


#endif
