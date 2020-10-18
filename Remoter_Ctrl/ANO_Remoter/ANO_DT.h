#ifndef __ANO_DT_H__
#define __ANO_DT_H__
#include "stm32f10x.h"
#include "ANO_Stick.h"

extern int16_t PLANE_YAW,PLANE_ROL,PLANE_PIT;

void ANO_DT_Send_RCData(void);
void ANO_DT_Send_RCData_To_Pc(void);
void ANO_DT_NrfData_Anl(u8 *data_buf , u8 num);
void ANO_DT_Send_Flag_To_Fly(u16 flag0, u16 flag1);
#endif
