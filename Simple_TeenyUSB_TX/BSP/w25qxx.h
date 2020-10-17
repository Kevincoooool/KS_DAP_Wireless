#ifndef __FLASH_H
#define __FLASH_H
#include "stm32f1xx.h"
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//W25Q64 代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//W25X系列/Q系列芯片列表
#define W25Q80 0XEF13
#define W25Q16 0XEF14
#define W25Q32 0XEF15
#define W25Q64 0XEF16
#define W25Q128 0XEF17

extern uint16_t W25QXX_TYPE; //定义W25QXX芯片型号

#define W25QXX_CS_SET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#define W25QXX_CS_RESET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)

//指令表
#define W25X_WriteEnable 0x06
#define W25X_WriteDisable 0x04
#define W25X_ReadStatusReg 0x05
#define W25X_WriteStatusReg 0x01
#define W25X_ReadData 0x03
#define W25X_FastReadData 0x0B
#define W25X_FastReadDual 0x3B
#define W25X_PageProgram 0x02
#define W25X_BlockErase 0xD8
#define W25X_SectorErase 0x20
#define W25X_ChipErase 0xC7
#define W25X_PowerDown 0xB9
#define W25X_ReleasePowerDown 0xAB
#define W25X_DeviceID 0xAB
#define W25X_ManufactDeviceID 0x90
#define W25X_JedecDeviceID 0x9F

uint8_t W25QXX_Init(void);
uint16_t W25QXX_ReadID(void);     //读取FLASH ID
uint8_t W25QXX_ReadSR(void);      //读取状态寄存器
void W25QXX_Write_SR(uint8_t sr); //写状态寄存器
void W25QXX_Write_Enable(void);   //写使能
void W25QXX_Write_Disable(void);  //写保护
void W25QXX_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void W25QXX_Read(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);    //读取flash
void W25QXX_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite); //写入flash
void W25QXX_Erase_Chip(void);                                                     //整片擦除
void W25QXX_Erase_Sector(uint32_t Dst_Addr);                                      //扇区擦除
void W25QXX_Wait_Busy(void);                                                      //等待空闲
void W25QXX_PowerDown(void);                                                      //进入掉电模式
void W25QXX_WAKEUP(void);                                                         //唤醒
#endif
