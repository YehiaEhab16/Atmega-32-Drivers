/*******************************************************/
/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: MCAL     		************/
/************		SWC: TWI 				************/
/************		Version: 1.00	 		************/
/************		Date: 12-10-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_config.h"
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"

void TWI_voidInitMaster(u8 Copy_u8Address)
{
	//Set Acknowledge bit
	SET_BIT(TWCR,TWCR_TWEA);

	//Set frequency to 400kHz , in case of 10Mhz crystal
	TWBR = 2;

	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);

	//Check if master will be addressed
	if(Copy_u8Address!=0)
	{
		TWAR = Copy_u8Address<<1;
	}

	//Enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidInitSlave(u8 Copy_u8Address)
{
	//Set Slave Address
	TWAR = Copy_u8Address<<1;

	//Set Acknowledge bit
	SET_BIT(TWCR,TWCR_TWEA);

	//Enable TWI
	SET_BIT(TWCR,TWCR_TWEN);
}

TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_Error=NoError;

	//Send start condition
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear the interrupt flag to start operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Wait until the operation finishes
	while((GET_BIT(TWCR, TWCR_TWINT))==0);

	//Check Operation Status
	if((TWSR & STATUS_MASK) != START_ACK)
	{
		Local_Error = StartConditionErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendRepeatedStart(void)
{
	TWI_ErrStatus Local_Error=NoError;

	//Send start condition
	SET_BIT(TWCR,TWCR_TWSTA);

	//Clear the interrupt flag to start operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Wait until the operation finishes
	while((GET_BIT(TWCR, TWCR_TWINT))==0);

	//Check Operation Status
	if((TWSR & STATUS_MASK) != REP_START_ACK)
	{
		Local_Error = RepeatedStartError;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error=NoError;

	//Send 7 slave address to bus
	TWDR = Copy_u8SlaveAddress<<1;

	//Set the write request in the LSB in data register
	CLR_BIT(TWDR,0);

	//Clear the start condition bit
	CLR_BIT(TWCR, TWCR_TWSTA);

	//Clear the interrupt flag to start operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Wait until the operation finishes
	while((GET_BIT(TWCR, TWCR_TWINT))==0);

	//Check Operation Status
	if((TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error = SlaveAddressWithWriteErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error=NoError;

	//Send 7 slave address to bus
	TWDR = Copy_u8SlaveAddress<<1;

	//Set the read request in the LSB in data register
	SET_BIT(TWDR,0);

	//Clear the start condition bit
	CLR_BIT(TWCR, TWCR_TWSTA);

	//Clear the interrupt flag to start operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Wait until the operation finishes
	while((GET_BIT(TWCR, TWCR_TWINT))==0);

	//Check Operation Status
	if((TWSR & STATUS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error = SlaveAddressWithReadErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_Error=NoError;

	//Write the data byte on the bus
	TWDR = Copy_u8DataByte;

	//Clear the interrupt flag to start operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Wait until the operation finishes
	while((GET_BIT(TWCR, TWCR_TWINT))==0);

	//Check Operation Status
	if((TWSR & STATUS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_Error = MasterWriteByteErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_pu8DataByte)
{
	TWI_ErrStatus Local_Error=NoError;

	//Clear the interrupt flag to allow slave to send data
	SET_BIT(TWCR, TWCR_TWINT);

	//Wait until the operation finishes
	while((GET_BIT(TWCR, TWCR_TWINT))==0);

	//Check Operation Status
	if((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_Error = MasterReadByteErr;
	}
	else
	{
		//Read the received data
		*Copy_pu8DataByte = TWDR;
	}

	return Local_Error;
}

void TWI_SendStopCondition(void)
{
	//Send stop condition on the bus
	SET_BIT(TWCR, TWCR_TWSTO);

	//Clear the interrupt flag to allow slave to send data
	SET_BIT(TWCR, TWCR_TWINT);
}
