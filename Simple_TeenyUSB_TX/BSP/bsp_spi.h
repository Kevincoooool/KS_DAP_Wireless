/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:26:31
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-11-07 09:58:55
 * @FilePath     : \Simple_TeenyUSB_TX\BSP\bsp_spi.h
 */
#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
void DAP_SPI_Init(void);
uint8_t SPI_RW_1(uint8_t dat) ;
uint8_t SPI_RW_2(uint8_t dat) ;
uint8_t SPI_TXRX(uint8_t *TXBuff,uint8_t *RXBuff,uint8_t cnt);
uint8_t SPI_TX(uint8_t *TXBuff,uint8_t cnt);
uint8_t SPI_TX7(uint8_t *TXBuff);
uint8_t SPI_TX4(uint8_t *TXBuff);
uint8_t SPI_TX2(uint8_t *TXBuff);   
void SPI_Switch(uint8_t ONOFF);
#endif















