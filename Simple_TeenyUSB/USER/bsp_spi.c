/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:32:30
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-05 10:44:48
 * @FilePath: \TeenyUSB\Wireless\bsp_spi.c
 */
#include "bsp_spi.h"
#include "hid_transfer.h"
#include "spi.h"
#include "gpio.h"
#include "dma.h"
void DAP_SPI_Init(void)
{
//	MX_GPIO_Init();
//	MX_DMA_Init();
//	MX_SPI1_Init();
//	MX_SPI2_Init();
//	HAL_SPI_Receive_DMA(&hspi1, USB_Response[USB_ResponseIndexI], DAP_PACKET_SIZE);
}

uint8_t SPI_RW(uint8_t dat)
{
	uint8_t d_read, d_send = dat;
	if (HAL_SPI_TransmitReceive(&hspi1, &d_send, &d_read, 1, 0xFF) != HAL_OK)
	{
		d_read = 0xFF;
	}
	return d_read;
}
