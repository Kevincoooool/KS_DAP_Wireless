#include "board.h"
#include "ano_drv_bkp.h"

void Bkp_Init(void)
{
    RCC->APB1RSTR |= 1<<27;        //重启BKP
    RCC->APB1RSTR &= ~(1<<27);
    RCC->APB1ENR|=1<<28;     //使能电源时钟     
    RCC->APB1ENR|=1<<27;     //使能BKP时钟 
}
void Write_Bkp(u8 reg,u16 data)
{ 
		PWR->CR|=1<<8;           //取消写保护
		switch(reg)
		{
				case 1:
						BKP->DR1=data;
						break;
				case 2:
						BKP->DR2=data;
						break;
				case 3:
						BKP->DR3=data;
						break;
				case 4:
						BKP->DR4=data;
						break;
				case 5:
						BKP->DR5=data;
						break;
				case 6:
						BKP->DR6=data;
						break;
				case 7:
						BKP->DR7=data;
						break;
				case 8:
						BKP->DR8=data;
						break;
				case 9:
						BKP->DR9=data;
						break;
				case 10:
						BKP->DR10=data;
						break;
		}
}
	 
	 
u16 Read_Bkp(u8 reg)
{
		u16 data;
 
		switch(reg)
		{
				case 1:
						data = BKP->DR1;
						break;
				case 2:
						data = BKP->DR2;
						break;
				case 3:
						data = BKP->DR3;
						break;
				case 4:
						data = BKP->DR4;
						break;
				case 5:
						data = BKP->DR5;
						break;
				case 6:
						data = BKP->DR6;
						break;
				case 7:
						data = BKP->DR7;
						break;
				case 8:
						data = BKP->DR8;
						break;
				case 9:
						data = BKP->DR9;
						break;
				case 10:
						data = BKP->DR10;
						break;
		}
 
		return data;
}

