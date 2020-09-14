/////////////////////////////////////////////////////////////
//// Auto generate by TeenyDT, http://dt.tusb.org
/////////////////////////////////////////////////////////////
#include "teeny_usb.h"

#define  COMP_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t COMP_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0xef,                                             /* bDeviceClass */
  0x02,                                             /* bDeviceSubClass */
  0x01,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  COMP_CONFIG_DESCRIPTOR_SIZE  (107)
__ALIGN_BEGIN  const uint8_t COMP_ConfigDescriptor [107] __ALIGN_END = {

  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
 0x6b, 0x00,                                       /* wTotalLength */
  0x03,                                             /* bNumInterfaces */

  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x18, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x01,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x88,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
};
#define  COMP_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  COMP_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  COMP_STRING_DESCRIPTOR1_STR   "KS_DIY"
#define  COMP_STRING_DESCRIPTOR1_SIZE   (14)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor1 [14] __ALIGN_END = {
  0x0e,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'K', 0x00,                                        /* wcChar0 */
  'S', 0x00,                                        /* wcChar1 */
  '_', 0x00,                                        /* wcChar2 */
  'D', 0x00,                                        /* wcChar3 */
  'I', 0x00,                                        /* wcChar4 */
  'Y', 0x00,                                        /* wcChar5 */
};
#define  COMP_STRING_DESCRIPTOR2_STR   "KS Wireless CMSIS-DAP"
#define  COMP_STRING_DESCRIPTOR2_SIZE   (44)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor2 [44] __ALIGN_END = {
  0x2c,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'K', 0x00,                                        /* wcChar0 */
  'S', 0x00,                                        /* wcChar1 */
  ' ', 0x00,                                        /* wcChar2 */
  'W', 0x00,                                        /* wcChar3 */
  'i', 0x00,                                        /* wcChar4 */
  'r', 0x00,                                        /* wcChar5 */
  'e', 0x00,                                        /* wcChar6 */
  'l', 0x00,                                        /* wcChar7 */
  'e', 0x00,                                        /* wcChar8 */
  's', 0x00,                                        /* wcChar9 */
  's', 0x00,                                        /* wcChar10 */
  ' ', 0x00,                                        /* wcChar11 */
  'C', 0x00,                                        /* wcChar12 */
  'M', 0x00,                                        /* wcChar13 */
  'S', 0x00,                                        /* wcChar14 */
  'I', 0x00,                                        /* wcChar15 */
  'S', 0x00,                                        /* wcChar16 */
  '-', 0x00,                                        /* wcChar17 */
  'D', 0x00,                                        /* wcChar18 */
  'A', 0x00,                                        /* wcChar19 */
  'P', 0x00,                                        /* wcChar20 */
};
#define  COMP_STRING_DESCRIPTOR3_STR   "996_996_996"
#define  COMP_STRING_DESCRIPTOR3_SIZE   (24)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor3 [24] __ALIGN_END = {
  0x18,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  '9', 0x00,                                        /* wcChar0 */
  '9', 0x00,                                        /* wcChar1 */
  '6', 0x00,                                        /* wcChar2 */
  '_', 0x00,                                        /* wcChar3 */
  '9', 0x00,                                        /* wcChar4 */
  '9', 0x00,                                        /* wcChar5 */
  '6', 0x00,                                        /* wcChar6 */
  '_', 0x00,                                        /* wcChar7 */
  '9', 0x00,                                        /* wcChar8 */
  '9', 0x00,                                        /* wcChar9 */
  '6', 0x00,                                        /* wcChar10 */
};
#define COMP_STRING_COUNT    (4)
const uint8_t* const COMP_StringDescriptors[4] = {
  COMP_StringDescriptor0,
  COMP_StringDescriptor1,
  COMP_StringDescriptor2,
  COMP_StringDescriptor3,
};
#define COMP_REPORT_DESCRIPTOR_SIZE_IF0  (24)
WEAK __ALIGN_BEGIN const uint8_t COMP_ReportDescriptor_if0[COMP_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x40,        //   Report Count (64)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    };



COMP_TXEP_MAX_SIZE
COMP_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors COMP_descriptors = {
  .device = COMP_DeviceDescriptor,
  .config = COMP_ConfigDescriptor,
  .strings = COMP_StringDescriptors,
  .string_cnt = COMP_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(COMP_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = COMP_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // COMP_WCID_DESCRIPTOR_SIZE)

#if defined(COMP_WCID_PROPERTIES_SIZE)
  .wcid_properties = COMP_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // COMP_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(COMP_WCID_BOS_SIZE)
  .wcid_bos = COMP_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // COMP_WCID_BOS_SIZE)

#if defined(COMP_WCID_DESC_SET_SIZE)
  .wcid_desc_set = COMP_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // COMP_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
