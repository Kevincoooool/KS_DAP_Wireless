/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:26:31
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-04 21:04:48
 * @FilePath: \TeenyUSB\Wireless\bsp_spi.h
 */
#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
void DAP_SPI_Init(void);
uint8_t SPI_RW(uint8_t dat) ;
#endif















