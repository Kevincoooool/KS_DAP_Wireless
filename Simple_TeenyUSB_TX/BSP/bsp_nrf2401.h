/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:26:31
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:28:00
 * @FilePath: \Simple_TeenyUSB\BSP\bsp_nrf2401.h
 */
#ifndef __DRV_NRF24L01_H__
#define __DRV_NRF24L01_H__

#include "stm32f1xx.h"

//ST7789端口定义
#define SPI_CSN_L()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)//RES
#define SPI_CSN_H()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)

#define SPI_CE_L()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET)//DC
#define SPI_CE_H()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET)


#define MODEL_RX				1			//普通接收
#define MODEL_TX				2			//普通发送
#define MODEL_RX2				3			//接收模式2,用于双向传输
#define MODEL_TX2				4			//发送模式2,用于双向传输

#define RX_PLOAD_WIDTH  65  	
#define TX_PLOAD_WIDTH  65  	
#define TX_ADR_WIDTH    5 	 	
#define RX_ADR_WIDTH    5   

//初始化,model=1/2/3/4,ch为实用的通道号
	void NRF_Init(uint8_t model, uint8_t ch);	
	//发送数据包,用于model 2/4
	void NRF_TxPacket(uint8_t * tx_buf, uint8_t len);	
	//发送数据包,用于model 3
	void NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len);	
	//检查NRF模块是否正常工作
	uint8_t NRF_Check(void);
	//检查是否有通信事件
	void NRF_Check_Event(void);
extern uint16_t Nrf_Err_cnt;
	extern uint8_t NRF24L01_2_RXDATA[RX_PLOAD_WIDTH];//nrf24l01接收到的数据
	extern uint8_t NRF24L01_2_TXDATA[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据
	extern uint8_t NRF_SSI,NRF_SSI_CNT;//NRF信号强度

uint8_t NRF_Connect(void);
	uint8_t NRF_Read_Reg(uint8_t reg);
	uint8_t NRF_Write_Reg(uint8_t reg, uint8_t value);
	uint8_t NRF_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);
	uint8_t NRF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);
extern uint8_t NRF_GETDATA;
#endif















