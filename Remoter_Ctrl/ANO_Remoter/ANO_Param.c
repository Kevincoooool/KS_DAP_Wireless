/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：玩物励志科技
 * 移植自  ：匿名科创
 * 淘宝    ：https://wanwulizhi.taobao.com
 * 技术Q群 ：572299632
*****************************************************************************/
#include "ANO_Param.h"
#include "ANO_Stick.h"
#include "ANO_Drv_MPU6050.h"

#define FIRSTINITFLAH  			0x44

struct param ANO_Param;

void ANO_Param_Init(void)//恢复默认参数
{
	ANO_Param.NRF_Channel= 0;
	ANO_Param.OffSet_En  = 0;
	ANO_Param.OffSet_Rol = 0;
	ANO_Param.OffSet_Pit = 0;
	ANO_Param.OffSet_Yaw = 0;
	ANO_Param.OffSet_Thr = 0;
	ANO_Param.FirstInitFlag = FIRSTINITFLAH;
	
	ANO_Param_SAVE();
}

void ANO_Param_SAVE(void)
{
	ANO_Flash_Write((u8 *)(&ANO_Param),sizeof(ANO_Param));
}

void ANO_Param_READ(void)
{
	ANO_Flash_Read((u8 *)(&ANO_Param),sizeof(ANO_Param));
	if(ANO_Param.FirstInitFlag != FIRSTINITFLAH)//板子从未初始化
	{
		ANO_Param_Init();
	}
}










