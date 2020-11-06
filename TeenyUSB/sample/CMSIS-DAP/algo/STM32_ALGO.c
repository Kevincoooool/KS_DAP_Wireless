/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"
#include "stdlib.h"
#include "string.h"

algo_info_t STM32_ALGO[6]={0};
void algo_init(void)
{
	memset(STM32_ALGO,0,sizeof(STM32_ALGO));
	STM32_ALGO[0].name="STM32F0XX";
	STM32_ALGO[1].name="STM32F1XX";
	STM32_ALGO[2].name="STM32F3XX";
	STM32_ALGO[3].name="STM32F4XX";
	STM32_ALGO[4].name="STM32F7XX";
	STM32_ALGO[5].name="STM32H7XX";

	memcpy(&STM32_ALGO[0].algo,&flash_algo_F0,sizeof(flash_algo_F0));
	memcpy(&STM32_ALGO[1].algo,&flash_algo_F1,sizeof(flash_algo_F1));
	memcpy(&STM32_ALGO[2].algo,&flash_algo_F3,sizeof(flash_algo_F3));
	memcpy(&STM32_ALGO[3].algo,&flash_algo_F4,sizeof(flash_algo_F4));
	memcpy(&STM32_ALGO[4].algo,&flash_algo_F7,sizeof(flash_algo_F7));
	memcpy(&STM32_ALGO[5].algo,&flash_algo_H7,sizeof(flash_algo_H7));
}
