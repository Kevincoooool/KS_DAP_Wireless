/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：玩物励志科技
 * 移植自  ：匿名科创
 * 淘宝    ：https://wanwulizhi.taobao.com
 * 技术Q群 ：572299632
*****************************************************************************/
#include "board.h"
#include "ANO_Drv_SPI.h"


void ANO_SPI_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_GPIO_SPI, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/*配置 SPI_NRF_SPI的 SCK,MISO,MOSI引脚 */ 
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_SCK| SPI_Pin_MISO| SPI_Pin_MOSI; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能 
	GPIO_Init(ANO_GPIO_SPI, &GPIO_InitStructure);
	
	/*SPI_NRF_SPI的 CSN 引脚:*/
	GPIO_InitStructure.GPIO_Pin = NRF_CSN_Pin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(NRF_CSN_GPIO, &GPIO_InitStructure);	
	
	/*SPI_NRF_SPI的 CE 引脚:*/
	GPIO_InitStructure.GPIO_Pin = NRF_CE_Pin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(NRF_CE_GPIO, &GPIO_InitStructure);	
	
	GPIO_SetBits(NRF_CSN_GPIO, NRF_CSN_Pin);
	GPIO_SetBits(NRF_CE_GPIO, NRF_CE_Pin);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主模式 
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //数据大小8位 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //时钟极性，空闲时为低 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //第1个边沿有效，上升沿为采样时刻 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS信号由软件产生 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //4分频，9MHz 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前 
	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	SPI_Init(SPI2, &SPI_InitStructure); 
	/* Enable SPI2 */ 
	SPI_Cmd(SPI2, ENABLE);
}

u8 ANO_SPI_RW(u8 dat) 
{ 
	/* 当 SPI发送缓冲器非空时等待 */ 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
	/* 通过 SPI2发送一字节数据 */ 
	SPI_I2S_SendData(SPI2, dat); 
	/* 当SPI接收缓冲器为空时等待 */ 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); 
	/* Return the byte read from the SPI bus */ 
	return SPI_I2S_ReceiveData(SPI2); 
}

void ANO_SPI_CSN_H(void)
{
	GPIO_SetBits(NRF_CSN_GPIO, NRF_CSN_Pin);
}

void ANO_SPI_CSN_L(void)
{
	GPIO_ResetBits(NRF_CSN_GPIO, NRF_CSN_Pin);
}



/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
