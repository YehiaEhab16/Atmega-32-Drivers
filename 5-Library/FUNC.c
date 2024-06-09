u16 combine(u16 Copy_u8First, u16 Copy_u8Second)
{
    u8 times=1;

    if(Copy_u8Second == 0)
    	return Copy_u8First*10;

    while(times<=Copy_u8Second)
        times *= 10;

    return Copy_u8First * times + Copy_u8Second;
}

u8 random(u8 Copy_u8Min, u8 Copy_u8Max)
{
	static u16 Local_u16Next = 3251;
	static u16 Local_u16Counter=0;
	Local_u16Next = (u16)((((u32)Local_u16Next * (u32)Local_u16Next) / 100UL ) % 10000UL);
	Local_u16Counter++;
	if(Local_u16Counter==50)
	{
		Local_u16Counter=0;
		Local_u16Next = 3251;
	}
	
	return Local_u16Next % (Copy_u8Max+1-Copy_u8Min) + Copy_u8Min ;
}

u16 reverse(u16 Copy_u16Number)
{
    u16 Local_u16Reverse=0;

    while (Copy_u16Number != 0)
    {
        Local_u16Reverse = Local_u16Reverse * 10;
        Local_u16Reverse = Local_u16Reverse + Copy_u16Number%10;
        Copy_u16Number = Copy_u16Number/10;
    }
    return Local_u16Reverse;
}

s32 mapping(s32 Copy_s32InputNumber, s32 Copy_s32InputMinimum, s32 Copy_s32InputMaximum, s32 Copy_s32OutputMinimum, s32 Copy_s32OutputMaximum)
{
	s32 Local_s32OutputNumber = (((Copy_s32OutputMaximum - Copy_s32OutputMinimum) / (Copy_s32InputMaximum - Copy_s32InputMinimum))*(Copy_s32InputNumber - Copy_s32InputMinimum)) + Copy_s32OutputMinimum;
	
	return Local_s32OutputNumber;
}