#ifndef __ANO_DRV_NRF24L01_H__
#define __ANO_DRV_NRF24L01_H__

#include "board.h"

#define MODEL_RX				1			//普通接收
#define MODEL_TX				2			//普通发送
#define MODEL_RX2				3			//接收模式2,用于双向传输
#define MODEL_TX2				4			//发送模式2,用于双向传输

#define RX_PLOAD_WIDTH  255  	
#define TX_PLOAD_WIDTH  255  	
#define TX_ADR_WIDTH    5 	 	
#define RX_ADR_WIDTH    5   


	void ANO_NRF_Init(u8 model, u8 ch);	//初始化,model=1/2/3/4,ch为实用的通道号
	void ANO_NRF_TxPacket(uint8_t * tx_buf, uint8_t len);	//发送数据包,用于model 2/4
	void ANO_NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len);	//发送数据包,用于model 3
	uint8_t ANO_NRF_Check(void);//检查NRF模块是否正常工作
	void ANO_NRF_Check_Event(void);//检查是否有通信事件
	void NRF_Check_Ch(void);//对频
		
	extern uint8_t RX_LEN;
	extern uint8_t NRF24L01_2_RXDATA[RX_PLOAD_WIDTH];//nrf24l01接收到的数据
	extern uint8_t NRF24L01_2_TXDATA[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据
	extern uint16_t NRF_SSI,NRF_SSI_CNT;//NRF信号强度
	extern u8 Check_Ch;
	extern uint8_t NRF_Evnet;
	
	uint8_t ANO_NRF_Read_Reg(uint8_t reg);
	uint8_t ANO_NRF_Write_Reg(uint8_t reg, uint8_t value);
	uint8_t ANO_NRF_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);
	uint8_t ANO_NRF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars);

#endif















