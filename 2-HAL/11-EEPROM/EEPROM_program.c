/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: EEPROM			************/
/************		Version: 1.00	 		************/
/************		Date: 13-10-2020 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include <util/delay.h>

#include "TWI_interface.h"

#include "EEPROM_config.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte)
{
	u8 Local_u8AddressPacket;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | A2_CONNECTION<<2 | Copy_u16LocationAddress>>8;

	//Send Start Condition
	TWI_SendStartCondition();

	//Send the address packet
	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	//Send the remaining 8 bits of location address
	TWI_MasterWriteDataByte((u8)Copy_u16LocationAddress);

	//Send the data byte to the memory location
	TWI_MasterWriteDataByte(Copy_u8DataByte);

	//Send stop condition
	TWI_SendStopCondition();

	//Delay until the write cycle is finished
	_delay_ms(10);
}

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress)
{
	u8 Local_u8AddressPacket, Local_u8Data;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (A2_CONNECTION<<2) | (Copy_u16LocationAddress>>8);

	//Send Start Condition
	TWI_SendStartCondition();

	//Send the address packet
	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	//Send the remaining 8 bits of location address
	TWI_MasterWriteDataByte((u8)Copy_u16LocationAddress);

	//Send repeated start to change write request to read
	TWI_SendRepeatedStart();

	//Send the address packet with read request
	TWI_SendSlaveAddressWithRead(Local_u8AddressPacket);

	//Get data from memory
	TWI_MasterReadDataByte(&Local_u8Data);

	//Send stop condition
	TWI_SendStopCondition();

	return Local_u8Data;
}
