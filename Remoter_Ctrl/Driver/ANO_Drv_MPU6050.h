#ifndef __ANO_DRV_MPU6050_H__
#define	__ANO_DRV_MPU6050_H__

#include "stm32f10x.h"
#include "ANO_Drv_I2C.h"

	extern u8 Acc_CALIBRATED;
	extern u8 Gyro_CALIBRATED;
	//extern Vector3i Acc_Offset,Gyro_Offset;

	//初始化6050
	void Init(uint16_t sample_rate, uint16_t lpf);
	//读取加速度
	void Read_Acc_Data(void);
	//读取角速度
	void Read_Gyro_Data(void);
	//返回加速度的值
	//Vector3f Get_Acc(void);
	//返回角速度的值
	//Vector3f Get_Gyro(void);
	//返回单位为度每秒的角速度
	//Vector3f Get_Gyro_in_dps(void);
	
#endif
