#include "ano_drv_flash.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
	
u8 ANO_Flash_Read(u8 *addr, u16 len)	//addr需要写入结构体的地址，len结构体长度
{
	for(u16 i=0; i<len; i=i+2)
	{
		u16 temp;
		if(i+1 <= len-1)
		{
			temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));
			addr[i] = BYTE0(temp);
			addr[i+1] = BYTE1(temp);
		}
		else
		{
			temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));
			addr[i] = BYTE0(temp);
		}

	}
	return 1;
}

u8 ANO_Flash_Write(u8 *addr, u16 len)
{
	uint16_t  FlashStatus;
	
	//解锁flash
	FLASH_Unlock();	
	
	FlashStatus = FLASH_ErasePage(PARAMFLASH_BASE_ADDRESS);//擦除整页
	if(FlashStatus != FLASH_COMPLETE)
		return 0;
	
	for(u16 i=0; i<len; i=i+2)
	{
		u16 temp;
		if(i+1 <= len-1)
			temp = (u16)(addr[i+1]<<8) + addr[i];
		else
			temp = 0xff00 + addr[i];
		
		FlashStatus = FLASH_ProgramHalfWord(PARAMFLASH_BASE_ADDRESS+i, temp);
        if (FlashStatus != FLASH_COMPLETE)
			return 0;
	}
	return 1;
}
