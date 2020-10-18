/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：玩物励志科技
 * 移植自  ：匿名科创
 * 淘宝    ：https://wanwulizhi.taobao.com
 * 技术Q群 ：572299632
*****************************************************************************/
#include "stm32f10x.h"
#include "sysconfig.h"
#include "ANO_Param.h"
#include "ANO_Drv_Flash.h"
uint8_t 	NRF_ENABLE = 0;

int main(void)
{
	//中断优先级组别设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//参数初始化
	ANO_Param_READ();
	
	//初始化USB
	USB_HID_Init();
	
	//初始化LED
	ANO_LED_Init();
	ANO_LED_0_FLASH();
	
	//初始化NRF所用SPI
	ANO_SPI_Init();
	//检查NRF连接是否正常
	NRF_ENABLE = ANO_NRF_Check();
	
	//如果连接正常，则将NRF初始化为主发送模式
	if(NRF_ENABLE)
	{
		ANO_NRF_Init(MODEL_TX2,ANO_Param.NRF_Channel);
		Show.NRF_Err = 0;
	}else Show.NRF_Err = 1;

	//初始化ADC采样
	ADC1_Init();
	
	//按键初始化
	KEY_Init();
	
	//初始化屏幕
	OLED_Init();
	
	//初始化系统滴答定时器,2ms中断
	SysTick_Config(SystemCoreClock / 500);
	OLED_ShowString(20, 1, "DAP Connect", 12,1); //绘制提示词
	OLED_Refresh_Gram();//开始显示
	while (1)
	{
		if(Show.oled_delay)
		{
//			oled_show();
//			OLED_Clear();
//			OLED_ShowString(20, 1, "DAP Connect", 12,1); //绘制提示词
			//Show_Duty();
			Show.oled_delay=0;
		}
	}
}
