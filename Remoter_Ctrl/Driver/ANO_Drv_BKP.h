#ifndef __ANO_DRV_BKP_H__
#define __ANO_DRV_BKP_H__

#include "stm32f10x.h"

void Bkp_Init(void);
void Write_Bkp(u8 reg,u16 data);
u16 Read_Bkp(u8 reg);

#endif
