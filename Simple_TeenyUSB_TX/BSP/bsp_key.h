/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:26:31
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 15:20:06
 * @FilePath     : \Simple_TeenyUSB_TX\BSP\bsp_spi.h
 */
#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#define KEY_UP HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)
#define KEY_OK HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)
#define KEY_DOWN HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)
void Key_Init(void);
uint8_t Scan_Key(void);
#endif















