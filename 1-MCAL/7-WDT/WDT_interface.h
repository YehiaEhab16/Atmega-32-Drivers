/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: WDT 				************/
/************		Version: 1.00	 		************/
/************		Date: 5-10-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_


#define SLEEP16_3ms	0
#define SLEEP32_5ms	1
#define SLEEP65ms		2
#define SLEEP0_13s		3
#define SLEEP0_26s		4
#define SLEEP0_52s		5
#define SLEEP1_0s		6
#define SLEEP2_1s		7

void WDT_voidEnable(void);
void WDT_voidDisable(void);
u8 WDT_u8Sleep(u8 Copy_u8SleepTime);


#endif
