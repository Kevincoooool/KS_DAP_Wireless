#ifndef __ANO_PARAM_H
#define __ANO_PARAM_H

#include "stm32f10x.h"
#include "ANO_Drv_Flash.h"

struct param{
	uint8_t  NRF_Channel;
	uint8_t  OffSet_En;
	uint16_t OffSet_Rol;
	uint16_t OffSet_Pit;
	uint16_t OffSet_Thr;
	uint16_t OffSet_Yaw;
	uint16_t FirstInitFlag;
};
extern struct param ANO_Param;

void ANO_Param_READ(void);
void ANO_Param_SAVE(void);

#endif

