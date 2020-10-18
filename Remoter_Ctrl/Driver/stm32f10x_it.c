#include "stm32f10x_it.h"
#include "usb_istr.h"
#include "ANO_Drv_Uart.h"

void USART1_IRQHandler(void)  //串口中断函数
{
	Uart1_IRQ();
}

void SysTick_Handler(void)
{
	SysTick_IRQ();
}
void USB_HP_CAN1_TX_IRQHandler(void)//USB_HP_CAN1_TX_IRQHandler
{
}
void USB_LP_CAN1_RX0_IRQHandler(void)//USB_LP_CAN1_RX0_IRQHandler 在这吃大亏啦，启动代码里面带1，这个不带，
{
    USB_Istr();
}

