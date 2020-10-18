/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:32:30
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 19:36:16
 * @FilePath     : \Simple_TeenyUSB_TX\BSP\bsp_spi.c
 */
#include "bsp_key.h"
#include "hid_transfer.h"
#include "spi.h"
#include "gpio.h"
#include "dma.h"
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
uint8_t Scan_Key(void)
{
	if (!KEY_UP)
	{
		HAL_Delay(200);
		if (!KEY_UP)
		{
			while (KEY_UP == !KEY_UP);
			return 1;
		}
	}
	if (!KEY_OK)
	{
		HAL_Delay(100);
		if (!KEY_OK)
		{
			while (KEY_OK == !KEY_OK)
				;
			
			return 2;
		}
	}
	if (!KEY_DOWN)
	{
		HAL_Delay(200);
		if (!KEY_DOWN)
		{
			while (KEY_DOWN == !KEY_DOWN)
				;
			
			return 3;
		}
	}
	return 0;
}

