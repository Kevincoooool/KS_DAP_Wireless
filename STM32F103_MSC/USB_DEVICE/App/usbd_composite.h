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
#include "usbd_storage_if.h"
#include "usbd_cdc_if.h"

#define WBVAL(x) (x & 0xFF),((x >> 8) & 0xFF)
#define DBVAL(x) (x & 0xFF),((x >> 8) & 0xFF),((x >> 16) & 0xFF),((x >> 24) & 0xFF)

#define USBD_IAD_DESC_SIZE           0x08
#define USBD_IAD_DESCRIPTOR_TYPE     0x0B



#define USBD_CDC_FIRST_INTERFACE     0          /* CDC FirstInterface */
#define USBD_CDC_INTERFACE_NUM       2          /* CDC Interface NUM */

#define USBD_CDC_CMD_INTERFACE       0
#define USBD_CDC_DATA_INTERFACE      1

#define USBD_MSC_FIRST_INTERFACE     2          /* MSC FirstInterface */
#define USBD_MSC_INTERFACE_NUM       1          /* MSC Interface NUM */

#define USBD_MSC_INTERFACE           2


#define MSC_INDATA_NUM              (MSC_EPIN_ADDR & 0x0F)
#define MSC_OUTDATA_NUM             (MSC_EPOUT_ADDR & 0x0F)

#define CDC_INDATA_NUM              (CDC_IN_EP & 0x0F)
#define CDC_OUTDATA_NUM             (CDC_OUT_EP & 0x0F)
#define CDC_OUTCMD_NUM              (CDC_CMD_EP & 0x0F)

#define USBD_COMPOSITE_DESC_SIZE    (9  + 58 + 8 +  32 + 8)


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
