/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_istr.c
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : ISTR events interrupt service routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile u16 wIstr;  /* ISTR register last read value */
volatile u8 bIntPackSOF = 0;  /* SOFs received between 2 consecutive packets */

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* function pointers to non-control endpoints service routines */
void (*pEpInt_IN[7])(void) =
  {
    EP1_IN_Callback,
    EP2_IN_Callback,
    EP3_IN_Callback,
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
  };

void (*pEpInt_OUT[7])(void) =
  {
    EP1_OUT_Callback,
    EP2_OUT_Callback,
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
  };


/*******************************************************************************
* Function Name  : USB_Istr
* Description    : STR events interrupt service routine
* Input          :
* Output         :
* Return         :
*******************************************************************************/
void USB_Istr(void)
{

	wIstr = _GetISTR();
	#if (IMR_MSK & ISTR_RESET)  //如果设置了USB中断
  	if (wIstr & ISTR_RESET & wInterrupt_Mask)
  	{
  		//ISTR 程式只能清0，无法写1，
  		 //用要清除的位为0，其他位写为1
    	_SetISTR((u16)CLR_RESET); 
    	Device_Property.Reset();
		#ifdef RESET_CALLBACK
    		RESET_Callback();
		#endif
  	}
	#endif
  	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	#if (IMR_MSK & ISTR_DOVR)
  	if (wIstr & ISTR_DOVR & wInterrupt_Mask)
  	{
    	_SetISTR((u16)CLR_DOVR);
		#ifdef DOVR_CALLBACK
    	DOVR_Callback();
		#endif
  	}
	#endif
   /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
  #if (IMR_MSK & ISTR_ERR)
  if (wIstr & ISTR_ERR & wInterrupt_Mask)
  {
    	_SetISTR((u16)CLR_ERR);
 		#ifdef ERR_CALLBACK
    	ERR_Callback();
		#endif
  	}
	#endif
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
  #if (IMR_MSK & ISTR_WKUP)
  if (wIstr & ISTR_WKUP & wInterrupt_Mask)
  {
   	 _SetISTR((u16)CLR_WKUP);
    Resume(RESUME_EXTERNAL);
	#ifdef WKUP_CALLBACK
    	WKUP_Callback();
	#endif
  }
  #endif
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
  #if (IMR_MSK & ISTR_SUSP)
  if (wIstr & ISTR_SUSP & wInterrupt_Mask)//USB掛起
  {
    	/* check if SUSPEND is possible */
    	if (fSuspendEnabled)  //usb掛起全能
    	{
      		Suspend();  //直接硬件掛起
    	}
    	else
    	{
    		//软件掛起
      		/* if not possible then resume after xx ms */
      		Resume(RESUME_LATER); // 枚举掛起
    	}
    	/* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    	_SetISTR((u16)CLR_SUSP);
		#ifdef SUSP_CALLBACK
    		SUSP_Callback();
		#endif
  	}
  	#endif
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	#if (IMR_MSK & ISTR_SOF) //帧首标志   //1ms enter one time
  	if (wIstr & ISTR_SOF & wInterrupt_Mask)
  	{
    	_SetISTR((u16)CLR_SOF);
    	bIntPackSOF++;  //帧指针加一

		#ifdef SOF_CALLBACK
    		SOF_Callback();
		#endif
  	}
	#endif
  	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	#if (IMR_MSK & ISTR_ESOF)
  	if (wIstr & ISTR_ESOF & wInterrupt_Mask)
  	{
    	_SetISTR((u16)CLR_ESOF); //帧期望标志
    	/* resume handling timing is made with ESOFs  */
    	Resume(RESUME_ESOF); /* request without change of the machine state */

		#ifdef ESOF_CALLBACK
    	ESOF_Callback();
		#endif
  	}
	#endif
  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	#if (IMR_MSK & ISTR_CTR)
  	if (wIstr & ISTR_CTR & wInterrupt_Mask)
  	{
    	/* servicing of the endpoint correct transfer interrupt */
    	/* clear of the CTR flag into the sub */
    	CTR_LP();
		#ifdef CTR_CALLBACK
    	CTR_Callback();
		#endif
  	}
	#endif
} /* USB_Istr */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

