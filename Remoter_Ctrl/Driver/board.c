#include "board.h"
#include "ANO_Scheduler.h"

static volatile uint32_t usTicks = 0;


void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

void Delay(vu32 nCount)
{
	for(; nCount!= 0;nCount--);
}

void SysTick_IRQ(void)
{
	Loop_check();
}

