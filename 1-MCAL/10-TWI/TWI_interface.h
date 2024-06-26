/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: TWI 				************/
/************		Version: 1.00	 		************/
/************		Date: 12-10-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


typedef enum My_Enum
{
	NoError,
	StartConditionErr,
	RepeatedStartError,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
}TWI_ErrStatus;

//Set Master address to 0 if master will not be addressed
void TWI_voidInitMaster(u8 Copy_u8Address);

void TWI_voidInitSlave(u8 Copy_u8Address);

TWI_ErrStatus TWI_SendStartCondition(void);

TWI_ErrStatus TWI_SendRepeatedStart(void);

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_pu8DataByte);

void TWI_SendStopCondition(void);


#endif
