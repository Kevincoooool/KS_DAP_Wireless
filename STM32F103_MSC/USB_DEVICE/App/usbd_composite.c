/**
 * @file        usbd_composite.c
 * @author      Weyne
 * @version     V01
 * @date        2016.10.28
 * @brief       MSC + CDC ¸´ºÏÉè±¸
 * @note
 * @attention   COYPRIGHT WEYNE
 */

#include "usbd_composite.h"
#include "usbd_cdc.h"
#include "usbd_msc.h"

static USBD_CDC_HandleTypeDef *pCDCData;
static USBD_MSC_BOT_HandleTypeDef *pMSCData;


static uint8_t  USBD_Composite_Init (USBD_HandleTypeDef *pdev,
                            uint8_t cfgidx);

static uint8_t  USBD_Composite_DeInit (USBD_HandleTypeDef *pdev,
                              uint8_t cfgidx);

static uint8_t  USBD_Composite_EP0_RxReady(USBD_HandleTypeDef *pdev);

static uint8_t  USBD_Composite_Setup (USBD_HandleTypeDef *pdev,
                             USBD_SetupReqTypedef *req);

static uint8_t  USBD_Composite_DataIn (USBD_HandleTypeDef *pdev,
                              uint8_t epnum);

static uint8_t  USBD_Composite_DataOut (USBD_HandleTypeDef *pdev,
                               uint8_t epnum);

static uint8_t  *USBD_Composite_GetFSCfgDesc (uint16_t *length);

static uint8_t  *USBD_Composite_GetDeviceQualifierDescriptor (uint16_t *length);

USBD_ClassTypeDef  USBD_COMPOSITE =
{
  USBD_Composite_Init,
  USBD_Composite_DeInit,
  USBD_Composite_Setup,
  NULL, /*EP0_TxSent*/
  USBD_Composite_EP0_RxReady,
  USBD_Composite_DataIn,
  USBD_Composite_DataOut,
  NULL,
  NULL,
  NULL,
  NULL,
  USBD_Composite_GetFSCfgDesc,
  NULL,
  USBD_Composite_GetDeviceQualifierDescriptor,
};

/* USB composite device Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
__ALIGN_BEGIN uint8_t USBD_Composite_CfgFSDesc[USBD_COMPOSITE_DESC_SIZE]  __ALIGN_END =
{
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
  WBVAL(USBD_COMPOSITE_DESC_SIZE),
  USBD_MAX_NUM_INTERFACES ,  /* bNumInterfaces: */
  0x01,   /* bConfigurationValue: */
  0x04,   /* iConfiguration: */
  0xC0,   /* bmAttributes: */
  0x96,   /* MaxPower 300 mA */


  /****************************CDC************************************/
  /* Interface Association Descriptor */
  USBD_IAD_DESC_SIZE,               // bLength
  USBD_IAD_DESCRIPTOR_TYPE,         // bDescriptorType
  USBD_CDC_FIRST_INTERFACE,         // bFirstInterface
  USBD_CDC_INTERFACE_NUM,           // bInterfaceCount
  0x02,                             // bFunctionClass
  0x02,                             // bFunctionSubClass
  0x01,                             // bInterfaceProtocol
  0x04,                             // iFunction

  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  USBD_CDC_CMD_INTERFACE,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x01,   /* iInterface: */

  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,

  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */

  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */

  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  USBD_CDC_CMD_INTERFACE,   /* bMasterInterface: Communication class interface */
  USBD_CDC_DATA_INTERFACE,   /* bSlaveInterface0: Data Class Interface */

  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  0x01,                           /* bInterval: */


  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  USBD_CDC_DATA_INTERFACE,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x02,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x01,   /* iInterface: */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x01,                              /* bInterval: ignore for Bulk transfer */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_IN_EP,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x01,                               /* bInterval: ignore for Bulk transfer */


 /****************************MSC************************************/
  /* Interface Association Descriptor */
  USBD_IAD_DESC_SIZE,                        // bLength
  USBD_IAD_DESCRIPTOR_TYPE,                  // bDescriptorType
  USBD_MSC_FIRST_INTERFACE,                  // bFirstInterface
  USBD_MSC_INTERFACE_NUM,                    // bInterfaceCount
  0x08,                                      // bFunctionClass
  0x06,                                      // bFunctionSubClass
  0x50,                                      // bInterfaceProtocol
  0x05,

  /********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,   /* bDescriptorType: */
  USBD_MSC_INTERFACE,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints*/
  0x08,   /* bInterfaceClass: MSC Class */
  0x06,   /* bInterfaceSubClass : SCSI transparent*/
  0x50,   /* nInterfaceProtocol */
  0x05,          /* iInterface: */

  /********************  Mass Storage Endpoints ********************/
  0x07,   /*Endpoint descriptor length = 7*/
  0x05,   /*Endpoint descriptor type */
  MSC_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_FS_PACKET),
  HIBYTE(MSC_MAX_FS_PACKET),
  0x01,   /*Polling interval in milliseconds */

  0x07,   /*Endpoint descriptor length = 7 */
  0x05,   /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_FS_PACKET),
  HIBYTE(MSC_MAX_FS_PACKET),
  0x01,     /*Polling interval in milliseconds*/

};


/* USB Standard Device Descriptor */
__ALIGN_BEGIN  uint8_t USBD_Composite_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};


/**
  * @brief  USBD_Composite_Init
  *         Initialize the Composite interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_Composite_Init (USBD_HandleTypeDef *pdev,
                            uint8_t cfgidx)
{
  uint8_t res = 0;

  pdev->pUserData =  &USBD_CDC_Interface_fops_FS;
  res +=  USBD_CDC.Init(pdev,cfgidx);
  pCDCData = pdev->pClassData;
  pdev->pUserData = &USBD_Storage_Interface_fops_FS;
  res +=  USBD_MSC.Init(pdev,cfgidx);
  pMSCData = pdev->pClassData;
  return res;
}

/**
  * @brief  USBD_Composite_DeInit
  *         DeInitilaize  the Composite configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
static uint8_t  USBD_Composite_DeInit (USBD_HandleTypeDef *pdev,
                              uint8_t cfgidx)
{
	uint8_t res = 0;
	pdev->pClassData = pCDCData;
	pdev->pUserData = &USBD_CDC_Interface_fops_FS;
	res +=  USBD_CDC.DeInit(pdev,cfgidx);

	pdev->pClassData = pMSCData;
	pdev->pUserData = &USBD_Storage_Interface_fops_FS;
	res +=  USBD_MSC.DeInit(pdev,cfgidx);

	return res;
}


static uint8_t  USBD_Composite_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
    return USBD_CDC.EP0_RxReady(pdev);
}



/**
* @brief  USBD_Composite_Setup
*         Handle the Composite requests
* @param  pdev: device instance
* @param  req: USB request
* @retval status
*/
static uint8_t  USBD_Composite_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  switch (req->bmRequest & USB_REQ_RECIPIENT_MASK)
  {
   case USB_REQ_RECIPIENT_INTERFACE:
     switch(req->wIndex)
      {
         case USBD_CDC_DATA_INTERFACE:
         case USBD_CDC_CMD_INTERFACE:
			 pdev->pClassData = pCDCData;
			 pdev->pUserData =  &USBD_CDC_Interface_fops_FS;
           return(USBD_CDC.Setup(pdev, req));

         case USBD_MSC_INTERFACE:
			 pdev->pClassData = pMSCData;
			 pdev->pUserData =  &USBD_Storage_Interface_fops_FS;
           return(USBD_MSC.Setup (pdev, req));

         default:
            break;
     }
     break;

   case USB_REQ_RECIPIENT_ENDPOINT:
     switch(req->wIndex)
     {

         case CDC_IN_EP:
         case CDC_OUT_EP:
         case CDC_CMD_EP:
			 pdev->pClassData = pCDCData;
			 pdev->pUserData =  &USBD_CDC_Interface_fops_FS;
           return(USBD_CDC.Setup(pdev, req));

         case MSC_EPIN_ADDR:
         case MSC_EPOUT_ADDR:
			 pdev->pClassData = pMSCData;
			 pdev->pUserData =  &USBD_Storage_Interface_fops_FS;
           return(USBD_MSC.Setup (pdev, req));

         default:
            break;
     }
     break;
  }
  return USBD_OK;
}




/**
* @brief  USBD_Composite_DataIn
*         handle data IN Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_Composite_DataIn (USBD_HandleTypeDef *pdev,
                              uint8_t epnum)
{
  switch(epnum)
  {
      case CDC_INDATA_NUM:
		pdev->pClassData = pCDCData;
		pdev->pUserData =  &USBD_CDC_Interface_fops_FS;
         return(USBD_CDC.DataIn(pdev,epnum));

      case MSC_INDATA_NUM:
			 pdev->pClassData = pMSCData;
			 pdev->pUserData =  &USBD_Storage_Interface_fops_FS;
         return(USBD_MSC.DataIn(pdev,epnum));

      default:
         break;

  }
  return USBD_FAIL;
}


/**
* @brief  USBD_Composite_DataOut
*         handle data OUT Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_Composite_DataOut (USBD_HandleTypeDef *pdev,
                               uint8_t epnum)
{
  switch(epnum)
  {
      case CDC_OUTDATA_NUM:
      case CDC_OUTCMD_NUM:
		pdev->pClassData = pCDCData;
		pdev->pUserData =  &USBD_CDC_Interface_fops_FS;
         return(USBD_CDC.DataOut(pdev,epnum));

      case MSC_OUTDATA_NUM:
			 pdev->pClassData = pMSCData;
			 pdev->pUserData =  &USBD_Storage_Interface_fops_FS;
         return(USBD_MSC.DataOut(pdev,epnum));

      default:
         break;

  }
  return USBD_FAIL;
}



/**
* @brief  USBD_Composite_GetHSCfgDesc
*         return configuration descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_Composite_GetFSCfgDesc (uint16_t *length)
{
   *length = sizeof (USBD_Composite_CfgFSDesc);
   return USBD_Composite_CfgFSDesc;
}

/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_Composite_GetDeviceQualifierDescriptor (uint16_t *length)
{
  *length = sizeof (USBD_Composite_DeviceQualifierDesc);
  return USBD_Composite_DeviceQualifierDesc;
}


/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/************************ (C) COPYRIGHT WEYNE *****END OF FILE****/



