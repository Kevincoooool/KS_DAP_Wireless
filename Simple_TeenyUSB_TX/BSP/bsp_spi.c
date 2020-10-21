/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:32:30
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 19:36:16
 * @FilePath     : \Simple_TeenyUSB_TX\BSP\bsp_spi.c
 */
#include "bsp_spi.h"
#include "spi.h"
#include "gpio.h"
#include "dma.h"
void DAP_SPI_Init(void)
{
	MX_GPIO_Init();
	MX_DMA_Init();
//	MX_SPI1_Init();
//	MX_SPI2_Init();
}

uint8_t SPI_RW_1(uint8_t dat)
{
	uint8_t d_read, d_send = dat;
	if (HAL_SPI_TransmitReceive(&hspi1, &d_send, &d_read, 1, 0xFF) != HAL_OK)
	{
		d_read = 0xFF;
	}
	return d_read;
}

uint8_t SPI_RW_2(uint8_t dat)
{
	uint8_t d_read, d_send = dat;
	if (HAL_SPI_TransmitReceive(&hspi2, &d_send, &d_read, 1, 0xFF) != HAL_OK)
	{
		d_read = 0xFF;
	}
	return d_read;
}
