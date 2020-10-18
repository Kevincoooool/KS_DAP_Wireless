#ifndef __ANO_DRV_I2C_H__
#define __ANO_DRV_I2C_H__

#include "board.h"

#define SCL_H         ANO_GPIO_I2C->BSRR = I2C_Pin_SCL
#define SCL_L         ANO_GPIO_I2C->BRR  = I2C_Pin_SCL
#define SDA_H         ANO_GPIO_I2C->BSRR = I2C_Pin_SDA
#define SDA_L         ANO_GPIO_I2C->BRR  = I2C_Pin_SDA
#define SCL_read      ANO_GPIO_I2C->IDR  & I2C_Pin_SCL
#define SDA_read      ANO_GPIO_I2C->IDR  & I2C_Pin_SDA

	void ANO_I2C_Init(void);
	int ANO_I2C_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);	
	int ANO_I2C_Single_Read(u8 SlaveAddress,u8 REG_Address);
	int ANO_I2C_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size);

#endif
