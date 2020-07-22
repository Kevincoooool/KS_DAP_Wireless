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
#include "usbd_customhid.h"
#include "usbd_custom_hid_if.h"

USBD_CDC_HandleTypeDef *pCDCData;
USBD_MSC_BOT_HandleTypeDef *pMSCData;
USBD_CUSTOM_HID_HandleTypeDef *pHIDData;


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
  /* 08*/
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
/*16*/
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
/*25*/
  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,
/*30*/
  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */
/*35*/
  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */
/*39*/
  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  USBD_CDC_CMD_INTERFACE,   /* bMasterInterface: Communication class interface */
  USBD_CDC_DATA_INTERFACE,   /* bSlaveInterface0: Data Class Interface */
/*44*/
  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  0x01,                           /* bInterval: */
/*51*/

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
/*60*/
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
/*67*/
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_IN_EP,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00,                               /* bInterval: ignore for Bulk transfer */
/*74*/

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
/*82*/
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
/*91*/
  /********************  Mass Storage Endpoints ********************/
  0x07,   /*Endpoint descriptor length = 7*/
  0x05,   /*Endpoint descriptor type */
  MSC_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_FS_PACKET),
  HIBYTE(MSC_MAX_FS_PACKET),
  0x00,   /*Polling interval in milliseconds */
/*98*/
  0x07,   /*Endpoint descriptor length = 7 */
  0x05,   /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_FS_PACKET),
  HIBYTE(MSC_MAX_FS_PACKET),
  0x00,     /*Polling interval in milliseconds*/
/*105*/

///****************************HID************************************/
  /* Interface Association Descriptor */
  USBD_IAD_DESC_SIZE,                        // bLength
  USBD_IAD_DESCRIPTOR_TYPE,                  // bDescriptorType
  USBD_HID_FIRST_INTERFACE,                  // bFirstInterface
  USBD_HID_INTERFACE_NUM,                    // bInterfaceCount
  0x03,                                      // bFunctionClass
  0x00,                                      // bFunctionSubClass
  0x00,                                      // bInterfaceProtocol
  0x00,
  /********************  HID interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,   /* bDescriptorType: */
  USBD_HID_INTERFACE,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints*/
  0x03,   /* bInterfaceClass: HID Class */
  0x00,   /* bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x00,   /* nInterfaceProtocol 0=none, 1=keyboard, 2=mouse*/
  0x00,          /* iInterface: */
    /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  CUSTOM_HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x10,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  USBD_CUSTOM_HID_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /********************  HID Endpoints ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/
  CUSTOM_HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  CUSTOM_HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  CUSTOM_HID_FS_BINTERVAL,          /*bInterval: Polling Interval (10 ms)*/
  /* 34 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/
  CUSTOM_HID_EPOUT_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  CUSTOM_HID_EPOUT_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  CUSTOM_HID_FS_BINTERVAL,          /*bInterval: Polling Interval (10 ms)*/

  /* 41 */
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
	pdev->pUserData =  (void *)NULL;
  res +=  USBD_CUSTOM_HID.Init(pdev,cfgidx);
  pHIDData = pdev->pClassData;
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
pdev->pClassData = pHIDData;
	pdev->pUserData = (void *)NULL;
	res +=  USBD_CUSTOM_HID.DeInit(pdev,cfgidx);

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
		 
		case USBD_HID_INTERFACE:
             pdev->pClassData = pHIDData;
             pdev->pUserData =  (void *)NULL;
           return(USBD_CUSTOM_HID.Setup (pdev, req));

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
		 
		case CUSTOM_HID_EPIN_ADDR:
         case CUSTOM_HID_EPOUT_ADDR:
             pdev->pClassData = pHIDData;
             pdev->pUserData = (void *)NULL;
           return(USBD_CUSTOM_HID.Setup (pdev, req));

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
		case HID_INDATA_NUM:
		 pdev->pClassData = pHIDData;
		 pdev->pUserData = (void *)NULL;
         return(USBD_CUSTOM_HID.DataIn(pdev,epnum));
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
		case HID_OUTDATA_NUM:
		 pdev->pClassData = pHIDData;
		 pdev->pUserData =  (void *)NULL;
         return(USBD_CUSTOM_HID.DataOut(pdev,epnum));
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



