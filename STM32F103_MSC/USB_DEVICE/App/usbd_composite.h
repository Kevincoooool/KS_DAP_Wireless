/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-20 20:31:30
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-07-22 12:43:57
 * @FilePath: \STM32F103_MSC\USB_DEVICE\App\usbd_composite.h
 */
/**
 * @file        usbd_composite.h
 * @author      Weyne
 * @version     V01
 * @date        2016.10.28
 * @brief       MSC + CDC ¸´ºÏÉè±¸
 * @note
 * @attention   COYPRIGHT WEYNE
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_COMPOSITE_H
#define __USBD_COMPOSITE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_msc.h"
#include  "usbd_cdc.h"
#include  "usbd_customhid.h"
#include "usbd_storage_if.h"
#include "usbd_cdc_if.h"

extern USBD_CDC_HandleTypeDef *pCDCData;
extern USBD_MSC_BOT_HandleTypeDef *pMSCData;
extern USBD_CUSTOM_HID_HandleTypeDef *pHIDData;

#define WBVAL(x) (x & 0xFF),((x >> 8) & 0xFF)
#define DBVAL(x) (x & 0xFF),((x >> 8) & 0xFF),((x >> 16) & 0xFF),((x >> 24) & 0xFF)

#define USBD_IAD_DESC_SIZE           0x08
#define USBD_IAD_DESCRIPTOR_TYPE     0x0B



#define USBD_CDC_FIRST_INTERFACE     0          /* CDC FirstInterface */
#define USBD_CDC_INTERFACE_NUM       2          /* CDC Interface NUM */

#define USBD_CDC_CMD_INTERFACE       0
#define USBD_CDC_DATA_INTERFACE      1


#define USBD_HID_FIRST_INTERFACE     3          /* HID FirstInterface */
#define USBD_HID_INTERFACE_NUM       1          /* HID Interface NUM */
#define USBD_HID_INTERFACE           3
	 
#define USBD_MSC_FIRST_INTERFACE     2          /* MSC FirstInterface */
#define USBD_MSC_INTERFACE_NUM       1          /* MSC Interface NUM */

#define USBD_MSC_INTERFACE           2



#define MSC_INDATA_NUM              (MSC_EPIN_ADDR & 0x0F)
#define MSC_OUTDATA_NUM             (MSC_EPOUT_ADDR & 0x0F)

#define HID_INDATA_NUM              (CUSTOM_HID_EPIN_ADDR & 0x0F)
#define HID_OUTDATA_NUM             (CUSTOM_HID_EPOUT_ADDR & 0x0F)


#define CDC_INDATA_NUM              (CDC_IN_EP & 0x0F)
#define CDC_OUTDATA_NUM             (CDC_OUT_EP & 0x0F)
#define CDC_OUTCMD_NUM              (CDC_CMD_EP & 0x0F)

#define USBD_COMPOSITE_DESC_SIZE    146


extern USBD_ClassTypeDef    USBD_COMPOSITE;

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USBD_MSC_H */
/**
  * @}
  */

/************************ (C) COPYRIGHT WEYNE *****END OF FILE****/
