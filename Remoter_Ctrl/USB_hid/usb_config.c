/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#include "usb_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#define BOOL bool
ErrorStatus HSEStartUpStatus;
void RTC_Configuration(void);
void Timer2Configuration(void);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USB_HW_KEY		//我这个板子没有软件复位usb，所以使用硬件复位
//#define USB_SOF_KEY				//usb软件复位，1.5k上拉电阻的三极管控制引脚
#define USB_DISCONNECT                      GPIOB  			//usb的开关引脚，1.5k上拉电阻的控制引脚
#define USB_DISCONNECT_PIN                  GPIO_Pin_14		//对于没有接控制引脚的，可以定义为空

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz).
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
  // Select USBCLK source 
     RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);  // 72MHZ sysclk
  //  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);

  /* Enable USB clock */
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode.
* Description    : Power-off system clocks and power while entering suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
	bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
     DEVICE_INFO *pInfo = &Device_Info;
  
  /* Set the device state to the correct state */
     if (pInfo->Current_Configuration != 0)
     {
    /* Device configured */
	 bDeviceState = CONFIGURED;
     }
     else 
     {
	 bDeviceState = ATTACHED;
     }
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config.
* Description    : Configures the USB interrupts.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
     NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{ 
#ifdef USB_SOF_KEY //usb软件复位，1.5k上拉电阻的三极管控制引脚
 	if (NewState != DISABLE)
	{
		GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
	}
	else
	{
		GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
	}
#endif
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_GPIO_Configuration(void)
{
#ifdef USB_SOF_KEY//usb软件复位，1.5k上拉电阻的三极管控制引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	/* USB_DISCONNECT used as USB pull-up */
     GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
     GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);
#endif
}
void DisableClock(void)
{
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_ALL,DISABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALL,DISABLE);
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
     u32 Device_Serial0, Device_Serial1, Device_Serial2;
     Device_Serial0 = *(u32*)(0x1FFFF7E8);
     Device_Serial1 = *(u32*)(0x1FFFF7EC);
     Device_Serial2 = *(u32*)(0x1FFFF7F0);
     if (Device_Serial0 != 0)
     {
         CustomHID_StringSerial[2] = (u8)(Device_Serial0 & 0x000000FF);  
	 CustomHID_StringSerial[4] = (u8)((Device_Serial0 & 0x0000FF00) >> 8);
	 CustomHID_StringSerial[6] = (u8)((Device_Serial0 & 0x00FF0000) >> 16);
	 CustomHID_StringSerial[8] = (u8)((Device_Serial0 & 0xFF000000) >> 24);
     
	 CustomHID_StringSerial[10] = (u8)(Device_Serial1 & 0x000000FF);  
	 CustomHID_StringSerial[12] = (u8)((Device_Serial1 & 0x0000FF00) >> 8);
	 CustomHID_StringSerial[14] = (u8)((Device_Serial1 & 0x00FF0000) >> 16);
	 CustomHID_StringSerial[16] = (u8)((Device_Serial1 & 0xFF000000) >> 24);
     
	 CustomHID_StringSerial[18] = (u8)(Device_Serial2 & 0x000000FF);  
	 CustomHID_StringSerial[20] = (u8)((Device_Serial2 & 0x0000FF00) >> 8);
	 CustomHID_StringSerial[22] = (u8)((Device_Serial2 & 0x00FF0000) >> 16);
	 CustomHID_StringSerial[24] = (u8)((Device_Serial2 & 0xFF000000) >> 24);
      }
}
void USB_Connect (BOOL con) 
{
#ifdef	USB_SOF_KEY	//软件开关usb
		USB_Cable_Config(con);			
#endif
#ifdef USB_HW_KEY	//usb硬件开关
//      *CNTR = CNTR_FRES;                         // Force USB Reset  
//      *ISTR = 0;                                 // Clear Interrupt Status  
//      if (con) {
//         *CNTR = CNTR_RESETM;                     // USB Reset Interrupt Mask  
//      } else {
//         *CNTR = CNTR_FRES | CNTR_PDWN;           // Switch Off USB Device  
//      }
//软件断开或开启USB的电源，从而实现USB的开启或关闭
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	if(con)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);    		  
	
   }  	
#endif
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
